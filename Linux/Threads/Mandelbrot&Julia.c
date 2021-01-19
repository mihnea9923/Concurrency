#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

char *in_filename_julia;
char *in_filename_mandelbrot;
char *out_filename_julia;
char *out_filename_mandelbrot;
int width, height;
int threads_number;
int **result;
int assigned_elements;
int unassigned_elements;
pthread_barrier_t barrier;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;	
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

typedef struct _complex
{
	double a;
	double b;
} complex;

typedef struct _params
{
	int is_julia, iterations;
	double x_min, x_max, y_min, y_max, resolution;
	complex c_julia;
} params;

params par;


void read_input_file(char *in_filename)
{
	FILE *file = fopen(in_filename, "r");
	if (file == NULL)
	{
		printf("Eroare la deschiderea fisierului de intrare!\n");
		exit(1);
	}

	fscanf(file, "%d", &par.is_julia);
	fscanf(file, "%lf %lf %lf %lf",
		   &par.x_min, &par.x_max, &par.y_min, &par.y_max);
	fscanf(file, "%lf", &par.resolution);
	fscanf(file, "%d", &par.iterations);

	if (par.is_julia)
	{
		fscanf(file, "%lf %lf", &par.c_julia.a, &par.c_julia.b);
	}

	fclose(file);
}

void write_output_file(char *out_filename)
{
	int i, j;

	FILE *file = fopen(out_filename, "w");
	if (file == NULL)
	{
		printf("Eroare la deschiderea fisierului de iesire!\n");
		return;
	}

	fprintf(file, "P2\n%d %d\n255\n", width, height);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fprintf(file, "%d ", result[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

int **allocate_memory()
{
	int **result;
	int i;
	result = malloc(height * sizeof(int *));
	if (result == NULL)
	{
		printf("Eroare la malloc!\n");
		exit(1);
	}

	for (i = 0; i < height; i++)
	{
		result[i] = malloc(width * sizeof(int));
		if (result[i] == NULL)
		{
			printf("Eroare la malloc!\n");
			exit(1);
		}
	}

	return result;
}

void free_memory()
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(result[i]);
	}
	free(result);
}

void get_args(int argc, char **argv)
{
	if (argc < 6)
	{
		printf("Numar insuficient de parametri:\n\t"
			   "./tema1 fisier_intrare_julia fisier_iesire_julia "
			   "fisier_intrare_mandelbrot fisier_iesire_mandelbrot\n");
		exit(1);
	}

	in_filename_julia = argv[1];
	out_filename_julia = argv[2];
	in_filename_mandelbrot = argv[3];
	out_filename_mandelbrot = argv[4];
	threads_number = atoi(argv[5]);
}

void run_Julia(int start_col, int start_row, int thread_elements)
{
	while (thread_elements)
	{
		int step = 0;
		complex z = {.a = start_col * par.resolution + par.x_min,
					 .b = start_row * par.resolution + par.y_min};

		while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par.iterations)
		{
			complex z_aux = {.a = z.a, .b = z.b};
			z.a = pow(z_aux.a, 2) - pow(z_aux.b, 2) + par.c_julia.a;
			z.b = 2 * z_aux.a * z_aux.b + par.c_julia.b;

			step++;
		}

		result[start_row][start_col] = step % 256;
		if (start_col < width - 1)
			start_col++;
		else
		{
			start_row++;
			start_col = 0;
		}

		thread_elements--; 
	}
}

void run_mandelbrot(int start_row, int start_col, int thread_elements)
{

	while (thread_elements)
	{
		complex c = {.a = start_col * par.resolution + par.x_min,
					 .b = start_row * par.resolution + par.y_min};
		complex z = {.a = 0, .b = 0};
		int step = 0;

		while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par.iterations)
		{
			complex z_aux = {.a = z.a, .b = z.b};

			z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + c.a;
			z.b = 2.0 * z_aux.a * z_aux.b + c.b;

			step++;
		}

		result[start_row][start_col] = step % 256;

		if (start_col < width - 1)
			start_col++;
		else
		{
			start_row++;
			start_col = 0;
		}

		thread_elements--;
	}
}

void convert_to_coordinates(int start, int end)
{
	for (int k = start; k < end; k++)
	{
		int *aux = result[k];
		result[k] = result[height - k - 1];
		result[height - k - 1] = aux;
	}
}


void *alg_par(void *arg)
{

	int i = *(int *)arg;
	int start_row, start_col;
	
	int rest = width * height % threads_number;
	int thread_elements = width * height / threads_number;
	int traversed_elements;
	if (rest > 0 && i < rest)
	{
		thread_elements += 1;
		traversed_elements = i * thread_elements;
	}
	else
	{
		traversed_elements = rest + i * thread_elements;
	}
	start_row = traversed_elements / width;
	start_col = traversed_elements % width;

	run_Julia(start_col, start_row, thread_elements);

	int start = i * assigned_elements;
	int end = 0;

	if (i < unassigned_elements)
	{
		end++;
		start += i;
	}
	else
	{
		start += unassigned_elements;
	}
	end += start + assigned_elements;
	pthread_barrier_wait(&barrier);
	convert_to_coordinates(start, end);
	pthread_barrier_wait(&barrier);
	if(i == 0)
		pthread_cond_signal(&cond);
	pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond2 , &mutex);
	pthread_mutex_unlock(&mutex);

	rest = width * height % threads_number;
	thread_elements = width * height / threads_number;

	if (rest > 0 && i < rest)
	{
		thread_elements += 1;
		traversed_elements = i * thread_elements;
	}
	else
	{
		traversed_elements = rest + i * thread_elements;
	}

	start_row = traversed_elements / width;
	start_col = traversed_elements % width;
	run_mandelbrot(start_row, start_col, thread_elements);

	start = i * assigned_elements;
	end = 0;

	if (i < unassigned_elements)
	{
		end++;
		start += i;
	}
	else
	{
		start += unassigned_elements;
	}
	end += start + assigned_elements;
	pthread_barrier_wait(&barrier);
	convert_to_coordinates(start, end);
	pthread_barrier_wait(&barrier);
	pthread_cond_signal(&cond);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

	pthread_t threads[threads_number];

	get_args(argc, argv);


	read_input_file(in_filename_julia);
	pthread_barrier_init(&barrier, NULL, threads_number);
	width = (par.x_max - par.x_min) / par.resolution;
	height = (par.y_max - par.y_min) / par.resolution;
	assigned_elements = (height / 2) / threads_number;
	unassigned_elements = (height / 2) % threads_number;

	result = allocate_memory();
	int *arg = (int *)malloc(threads_number * sizeof(int));

	for (int i = 0; i < threads_number; i++)
	{
		arg[i] = i;
		pthread_create(&threads[i], NULL, alg_par, (void *)&arg[i]);
	}

	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond , &mutex);
	write_output_file(out_filename_julia);
	free_memory();

	read_input_file(in_filename_mandelbrot);

	width = (par.x_max - par.x_min) / par.resolution;
	height = (par.y_max - par.y_min) / par.resolution;

	assigned_elements = (height / 2) / threads_number;
	unassigned_elements = (height / 2) % threads_number;
	result = allocate_memory();
	
	pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond2);
	pthread_mutex_lock(&mutex2);
	pthread_cond_wait(&cond , &mutex2);
    
	pthread_mutex_unlock(&mutex2);
	write_output_file(out_filename_mandelbrot);
	pthread_barrier_destroy(&barrier);
	free(arg);
	free_memory();

	return 0;
}

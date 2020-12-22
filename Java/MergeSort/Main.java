import java.util.Random;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int size = 512;
        int array[] = new int[size];
        long x = System.nanoTime();
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(size * 10);
        }

        //  SortThread th = new SortThread(array, 0, size - 1);
        //  th.run();
        Coordinator coordinator = new Coordinator(array);
        int threadsNumber = 4;
        Merge threads[] = new Merge[threadsNumber];
        for (int i = 0; i < threadsNumber; i++) {
            threads[i] = new Merge(array, coordinator);
            threads[i].start();
        }
        for (int i = 0; i < threadsNumber; i++) {
            threads[i].join();
        }
       
        for(int i = 0 ; i < size - 1; i++)
        {
            if(array[i] > array[i + 1])
            {
                System.out.println("error");
                return;
            }
        }
        System.out.println("good");
        long y = System.nanoTime();
        System.out.println((y - x) / 1000000000);
    }
}
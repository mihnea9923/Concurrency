import java.util.Random;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int size = 1000000;
        int array[] = new int[size];
        int threadsNumber = 4;
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(size * 10);
        }
        long startTime = System.nanoTime();
        QuickSort sort[] = new QuickSort[threadsNumber];
        Coordinator coordinator = new Coordinator(threadsNumber);
        coordinator.addSubArray(0, size - 1);
        for (int i = 0; i < threadsNumber; i++) {
            sort[i] = new QuickSort(array, coordinator);
            sort[i].start();
        }
        for (int i = 0; i < threadsNumber; i++) {
            sort[i].join();
        }

        isSorted(array, size);
        System.out.println(coordinator.t1);
        System.out.println(coordinator.t2);
        System.out.println(coordinator.t3);
        System.out.println(coordinator.t4);
        System.out.println((System.nanoTime() - startTime) / 1000000000);

    }

    private static void isSorted(int array[], int size) {
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) {
                System.out.println("Not sorted");
                return;
            }
        }
        System.out.println("Sorted right");
    }
}


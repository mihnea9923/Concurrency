import java.util.Map.Entry;

public class QuickSort extends Thread {
    private int[] array;
    private int left;
    private int right;
    private int pivotIndex;
    private Coordinator coordinator;

    public QuickSort(int array[], Coordinator coordinator) {
        this.array = array;
        this.coordinator = coordinator;
    }

    public void run() {
        try {
            sort(array);
        } catch (InterruptedException e) {
        }
    }

    private void sort(int array[]) throws InterruptedException {
            while(coordinator.isFinished() == false)
            {
                Entry<Integer, Integer> pair = coordinator.getSubArray();
                if(Thread.currentThread().getName().contains("0"))
                    coordinator.t1++;
                if(Thread.currentThread().getName().contains("1"))
                    coordinator.t2++;
                if(Thread.currentThread().getName().contains("2"))
                    coordinator.t3++;
                if(Thread.currentThread().getName().contains("3"))
                    coordinator.t4++;

                left = pair.getKey().intValue();
                right = pair.getValue().intValue();
                if(left == -1)
                    break;
                int pivot = partition(array, left, right);
                if(left < pivot - 1)
                {
                    coordinator.addSubArray(left, pivot - 1);
                }
                if(pivot + 1 < right)
                {
                    coordinator.addSubArray(pivot + 1, right);
                }
                coordinator.workerFinished();
            }


    }

    private int partition(int[] array, int left, int right) {
        int pivot = left - 1;
        for (int i = left; i < right; i++) {
            if (array[i] <= array[right]) {
                pivot++;
                swap(array, i, pivot);
            }
        }
        pivot++;
        swap(array, right, pivot);
        pivotIndex = pivot;
        return pivot;
    }

    private void swap(int array[], int i, int pivot) {
        int temp = array[i];
        array[i] = array[pivot];
        array[pivot] = temp;
    }

    public int getPivot() {
        return pivotIndex;
    }
}

public class Merge extends Thread {
    private int[] array;
    private int left;
    private int right;
    private Coordinator coordinator;

    public Merge(int array[], Coordinator coordinator) {
        this.array = array;
        this.coordinator = coordinator;
    }

    public void setSubArray(int left, int right) {
        this.left = left;
        this.right = right;
    }

    public Merge() {

    }

    public void run() {
        while (coordinator.isNotFinished()) {
            try {
                if(coordinator.threadStarts() == false)
                {
                    break;
                }
            } catch (InterruptedException e) {
            }
            left = coordinator.getLeft();
            right = coordinator.getRight();
            int mid = (left + right) / 2;
            merge(left, mid, right, array);
            coordinator.threadFinished();
        }
    }

    public void merge(int left, int mid, int right, int v[]) {
        
        int leftArray[] = new int[mid - left + 1];
        int rightArray[] = new int[right - mid];
        int leftArrayIndex = 0;
        int rightArrayIndex = 0;

        for (int i = left; i <= mid; i++) {
            leftArray[leftArrayIndex] = v[i];
            leftArrayIndex++;
        }
        for (int i = mid + 1; i <= right; i++) {
            rightArray[rightArrayIndex] = v[i];
            rightArrayIndex++;
        }
        int i = 0, j = 0, k = left;
        while (i < leftArrayIndex && j < rightArrayIndex) {
            if (leftArray[i] < rightArray[j]) {
                v[k] = leftArray[i];
                i++;
            } else {
                v[k] = rightArray[j];
                j++;
            }
            k++;
        }
        while (i < leftArrayIndex) {
            v[k] = leftArray[i];
            i++;
            k++;
        }
        while (j < rightArrayIndex) {
            v[k] = rightArray[j];
            j++;
            k++;
        }

    }
}
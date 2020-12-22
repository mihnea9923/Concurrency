public class Coordinator {
    private int[] array;
    int left;
    int right;
    int size;
    volatile int unsortedSubArrays;
    boolean finished = false;

    public Coordinator(int array[]) {
        this.array = array;
        left = 0;
        size = 2;
        right = -1;
        unsortedSubArrays = array.length / 2 + array.length % 2;
    }

    public int getLeft() {
        return left;
    }

    public int getRight() {
        return right;
    }

    public synchronized void updateLeftAndRight() throws InterruptedException {

            left = right + 1;
            right += size;
    }

    public synchronized void threadFinished() {
        if(size == array.length)
        {
            finished = true;
            notifyAll();
            return;
        }
        if (unsortedSubArrays == 0) {
            right = -1;
            size *= 2;
        
            System.out.println(size);
            unsortedSubArrays = array.length / size ;
            notifyAll();
        }
    }

    public synchronized boolean threadStarts() throws InterruptedException {
        while (unsortedSubArrays <= 0 && !finished)
        {
            wait();
        }
        unsortedSubArrays--;
        updateLeftAndRight();
        return !finished;
    }
    public boolean isNotFinished()
    {
        return finished == false;
    }

}
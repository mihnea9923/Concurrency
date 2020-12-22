import java.util.Map.Entry;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;

public class Coordinator {
    private boolean finished = false;
    List<Entry<Integer, Integer>> subArrays = new ArrayList<>();
    private volatile int workingThreads;
    public volatile int t1 = 0;
    public volatile int t2 = 0;
    public volatile int t3 = 0;
    public volatile int t4 = 0;

    public Coordinator(int threadsNumber) {
        this.workingThreads = 0;
    }

    public boolean isFinished() {
        return finished;
    }

    public synchronized void addSubArray(int left, int right) {
        Entry<Integer, Integer> pair = new AbstractMap.SimpleEntry<Integer, Integer>(left, right);
        subArrays.add(pair);
        if (subArrays.size() == 1) {
            notifyAll();
        }
    }

    public synchronized Entry<Integer, Integer> getSubArray() throws InterruptedException {
        workingThreads++;
        while (subArrays.size() == 0 && isFinished() == false) {
                workingThreads--;
            if (workingThreads == 0) {
                finished = true;
                notifyAll();
            } else {
                wait();
            }
            workingThreads++;
        }
        if (isFinished()) {
            return new AbstractMap.SimpleEntry<Integer, Integer>(-1, -1);
        }
        Entry<Integer, Integer> pair = subArrays.get(0);
        subArrays.remove(0);
        
        return pair;
    }

    public  void workerFinished() {
        if (workingThreads > 0) {
            workingThreads--;

        }
        if (workingThreads == 0 && subArrays.size() == 0) {
            finished = true;
            notifyAll();
        }
    }

}


public class Computer  {
    public volatile int waitingCars1 = 0;
    public volatile int waitingCars2 = 0;
    public volatile int cars1Inside = 0;
    public volatile int cars2Inside = 0;
    public boolean running = true;
    private MySemaphore semaphore1;
    private MySemaphore semaphore2;

    public Computer(MySemaphore semaphore1, MySemaphore semaphore2) {
        this.semaphore1 = semaphore1;
        this.semaphore2 = semaphore2;
    }

    public void switchSemaphors() throws InterruptedException {
        if (semaphore1.canPass() && waitingCars2 > 0) {
            semaphore1.toggle();
            while (cars1Inside > 0)
                ;
            semaphore2.toggle();

        } else if (semaphore2.canPass() && waitingCars1 > 0) {
            semaphore2.toggle();
            while (cars2Inside > 0)
                ;
            semaphore1.toggle();
        }
    }

    

    public boolean running() {
        return running;
    }

    public synchronized void finish() {
        running = false;
    }

    public synchronized void car2IsComing() {
        waitingCars2++;
    }

    public synchronized void car2Enters() {
        waitingCars2--;
        cars2Inside++;
    }

    public synchronized void car1IsComing() {
        waitingCars1++;
    }

    public synchronized void car1Enters() {
        waitingCars1--;
        cars1Inside++;
    }

    public synchronized void car1Exits() {
        cars1Inside--;
    }

    public synchronized void car2Exits() {
        cars2Inside--;
    }

}
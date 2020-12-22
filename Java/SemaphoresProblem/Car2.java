public class Car2 extends Thread {
    private Computer computer;
    private MySemaphore semaphore;

    public Car2(Computer computer, MySemaphore semaphore) {
        this.computer = computer;
        this.semaphore = semaphore;
    }

    public void run() {
        computer.car2IsComing();
        try {
            sleep(1000);
        } catch (InterruptedException e) {
        }
        cantPass();
        computer.car2Enters();
        System.out.println("Car2 is passing");
        try {
            sleep(1000);
        } catch (InterruptedException e) {
        }
        computer.car2Exits();

    }

    public void cantPass() {

        while (semaphore.canPass() == false) {
       }
    }
}
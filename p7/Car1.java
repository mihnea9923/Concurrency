public class Car1 extends Thread {
    private Computer computer;
    private MySemaphore semaphore;

    public Car1(Computer computer, MySemaphore semaphore) {
        this.computer = computer;
        this.semaphore = semaphore;
    }

    public void run() {
        //semnalam faptul ca ajungem la semafor
        computer.car1IsComing();
        try {
            sleep(1000);
        } catch (InterruptedException e1) {
        }
        //asteptam cat timp semaforul e rosu
        cantPass();
        //traversam
        computer.car1Enters();
        System.out.println("Car1 is passing");
        try {
            sleep(1000);
        } catch (InterruptedException e) {
        }
        //semnalam ca am trecut
        computer.car1Exits();

    }

    public void cantPass() {
        while (semaphore.canPass() == false) {

        }
    }
}
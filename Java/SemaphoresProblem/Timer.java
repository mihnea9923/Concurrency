public class Timer extends Thread {
    private Computer computer;

    public Timer(Computer computer) {
        this.computer = computer;
    }
    public void run() {
        while (computer.running()) {
            try {
                computer.switchSemaphors();
                Thread.sleep(5000);
            } catch (InterruptedException e) {
            }
        }
    }
}

import java.util.ArrayList;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class ProductionPoint {
    private int size;
    private ArrayList<ProducerRobot> producers = new ArrayList<ProducerRobot>();
    //we could use a queue/blocking queue instead but I thought it's not required to take them in any particular order so a list is fine
    private ArrayList<Vaccine> vaccines = new ArrayList<Vaccine>();
    private ProductionPointSurface surface;
    private Semaphore semaphore = new Semaphore(10);

    // private volatile int vaccinesNr = 0;
    public ProductionPoint(int size) {
        this.size = size;
        surface = new ProductionPointSurface(size);
    }

    public ProductionPointSurface getSurface() {
        return surface;
    }

    public  void getRobotsPosition() {
        for (ProducerRobot producerRobot : producers) {
            producerRobot.getPosition();
        }
    }

    public void read() throws InterruptedException {
        semaphore.acquire();
        // I don't know what this reading is for so i'm just gonna throw a for loop here
        for (var vaccine : vaccines) {

        }
        semaphore.release();
    }

    public synchronized void newVaccin(Vaccine vaccine) {
        // vaccinesNr++;
        vaccines.add(vaccine);
        notify();
    }

    public void generateProducers() throws InterruptedException {
        while (producers.size() < size / 2) {
            ProducerRobot robot = new ProducerRobot(this);
            do {
                robot.generatePosition(size);
            } while (surface.positionBusy(robot));
            producers.add(robot);
            robot.start();
            Thread.currentThread().sleep(ThreadLocalRandom.current().nextInt(500, 1000));

        }
    }

    public synchronized Vaccine giveVaccine() {
        while (vaccines.size() == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        Vaccine lastVaccine = vaccines.get(vaccines.size() - 1);
        vaccines.remove(lastVaccine);
        return lastVaccine;
    }

}
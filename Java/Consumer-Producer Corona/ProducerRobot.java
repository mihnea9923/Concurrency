import java.security.KeyStore.Entry;
import java.util.Random;
import java.util.UUID;
import java.util.concurrent.ThreadLocalRandom;

public class ProducerRobot extends Thread {
    
    private int x;
    private int y;
    ProductionPointSurface surface;
    ProductionPoint productionPoint;
    //i will initialize it with 300 on default
    private int waitingTime = 300;
    public ProducerRobot(ProductionPoint productionPoint) {
        this.productionPoint = productionPoint;
        this.surface = productionPoint.getSurface();
    }

    public ProducerRobot(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public void setWaitingTime(int waitingTime)
    {
        this.waitingTime = waitingTime;
    }
    public void run() {
        while (true) {
            try {
                move();
                Thread.currentThread().sleep(waitingTime);
            } catch (InterruptedException e) {
            }
            Vaccine vaccine = new Vaccine(UUID.randomUUID().toString());
            productionPoint.newVaccin(vaccine);
        }
    }
    
	public synchronized int[] getPosition() {
        int position[] = new int[2];
        position[0] = x;
        position[1] = y;
        return position;
    }
    public void generatePosition(int bound)
    {
        Random random = new Random();
        x = random.nextInt(bound);
        y = random.nextInt(bound);
    }
    public int getX()
    {
        return x;
    }
    public int getY()
    {
        return y;
    }
    public synchronized void move() throws InterruptedException
    {
        int[] position = new int[2];
        //i put them into a vector because i am gonna change their values inside "surface" object so I would need to pass them by 
        //reference which is not possible in java
        position[0] = x;
        position[1] = y;
        while(surface.availablePosition(position) == false)
        {
            Thread.currentThread().sleep(ThreadLocalRandom.current().nextInt(50, 100));
        }
    }

}
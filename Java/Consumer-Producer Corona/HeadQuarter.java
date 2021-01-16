import java.util.ArrayList;

public class HeadQuarter {
    private ArrayList<TransporterRobot> transporters = new ArrayList<TransporterRobot>();
    private ArrayList<ProductionPoint> productionPoints = new ArrayList<>();
    private ArrayList<Vaccine> vaccines = new ArrayList<>();
    private int robots;

    public HeadQuarter(int robots) throws InterruptedException {
        this.robots = robots;
        createProductionPoints();
        generateProducers();
        generateTransporters();
        startTransporters();
    }

    private void createProductionPoints() {
        int productionNumber = (int)(Math.random() * (5 - 1)) + 1;
        for(int i = 0 ; i < productionNumber ;  i++)
            productionPoints.add(new ProductionPoint((int)(Math.random() * (500 - 100)) + 100));

    }

    public void generateProducers() {
        for (ProductionPoint productionPoint : productionPoints) {
            try {
                productionPoint.generateProducers();
            } catch (InterruptedException e) {
            }
    }
    }
   
    public void generateTransporters()
    {
        int productionPoint = -1;
        for(int i = 0 ; i < robots ; i++)
        {
            //we will make it sure that each production point gets an equal amount of transporters
            if(i % productionPoints.size() == 0)
                productionPoint++;
            transporters.add(new TransporterRobot(productionPoints.get(productionPoint),this));
        }
    }
    public void startTransporters()
    {
        for (TransporterRobot transporter : transporters) {
            transporter.start();
        }
    }
    public synchronized void receiveVaccine(Vaccine vaccine)
    {
        vaccines.add(vaccine);
    }
}
public class TransporterRobot extends Thread {
    private ProductionPoint productionPoint;
    private HeadQuarter headQuarter;
    private Vaccine vaccine;

    public TransporterRobot(ProductionPoint point, HeadQuarter headQuarter) {
        productionPoint = point;
        this.headQuarter = headQuarter;
    }

    public void run() {
        while (true) {
            receiveVaccine();
            giveVaccine();
            try {
                sleep(50);
            } catch (InterruptedException e) {
            }
        }
    }

    public void receiveVaccine() {
        Vaccine vaccine = productionPoint.giveVaccine();
        setVaccine(vaccine);
    }

    public void setVaccine(Vaccine vaccine) {
        this.vaccine = vaccine;
    }

    public void giveVaccine() {
        headQuarter.receiveVaccine(vaccine);
    }

}
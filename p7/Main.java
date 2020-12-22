public class Main{
    public static void main(String[] args) throws InterruptedException {
        MySemaphore semaphore1 = new MySemaphore(true);
        MySemaphore semaphore2 = new MySemaphore(false);
        Computer computer = new Computer(semaphore1 , semaphore2);
        Timer timer = new Timer(computer);
        timer.start();

        for(int i = 0 ;i < 100 ; i++)
        {
            
            if(i % 2 == 0)
            {
                Car1 car = new Car1(computer , semaphore1);
                car.start();
            }
            else
            {
                Car2 car2 = new Car2(computer , semaphore2);
                car2.start();
            }   
            Thread.sleep(100);
        }
        Thread.sleep(1000);
        computer.finish();
    }
}
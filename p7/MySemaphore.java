
public class MySemaphore {
    private volatile boolean isGreen;

    public MySemaphore(boolean isGreen) {
        this.isGreen = isGreen;
    }

    public  boolean canPass() {
        return isGreen;
    }

    public  void toggle() {
        isGreen = !isGreen;
    }
}

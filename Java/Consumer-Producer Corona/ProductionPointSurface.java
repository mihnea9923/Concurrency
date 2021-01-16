public class ProductionPointSurface {
    boolean[][] positions;
    int size;

    public ProductionPointSurface(int size) {
        this.size = size;
        positions = new boolean[size][size];
        initializePositions();
    }

    public void initializePositions() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                positions[i][j] = false;
    }

    public void togglePositionState(int x, int y) {
        positions[x][y] = !positions[x][y];
    }

    public boolean positionBusy(ProducerRobot robot) {
        return positions[robot.getX()][robot.getY()];
    }
    public boolean positionBusy(int x , int y)
    {
        return positions[x][y];
    }

    public synchronized boolean availablePosition(int[] position) {
        int robotX = position[0];
        int robotY = position[1];
        
        if(outOfBounds(robotX - 1, robotY) == false && positionBusy(robotX - 1, robotY) == false)
        {
            
            position[0] = robotX - 1;
            position[1] = robotY;
            togglePositionState(position[0], position[1]);
            //mark robot's last position as not busy
            togglePositionState(robotX, robotY);
            return true;
        }
        if(outOfBounds(robotX + 1, robotY) == false && positionBusy(robotX + 1, robotY) == false)
        {
            position[0] = robotX + 1;
            position[1] = robotY;
            togglePositionState(position[0], position[1]);
            togglePositionState(robotX, robotY);
            return true;
        }
        if(outOfBounds(robotX, robotY - 1) == false && positionBusy(robotX , robotY - 1) == false)
        {
            position[0] = robotX;
            position[1] = robotY - 1;
            togglePositionState(position[0], position[1]);
            togglePositionState(robotX, robotY);
            return true;
        }
        if(outOfBounds(robotX , robotY + 1) == false && positionBusy(robotX , robotY + 1) == false)
        {
            position[0] = robotX;
            position[1] = robotY + 1;
            togglePositionState(position[0], position[1]);
            togglePositionState(robotX, robotY);
            return true;
        }
        return false;
    }

    public boolean outOfBounds(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size)
            return false;
        return true;
    }
}
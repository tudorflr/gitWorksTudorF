package Model;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class Server implements Runnable{

    private int serverId;
  //  private int numberOfTasks = 0;

    private final AtomicInteger waitingPeriod = new AtomicInteger(0);
    private final AtomicInteger numberOfTasks = new AtomicInteger(0);
    private BlockingQueue<Task> taskQueue = new LinkedBlockingQueue<>();

    private List<Integer> waitingPeriods = new ArrayList<>();

    private volatile boolean running = true;

    public void addTask(Task task) throws InterruptedException {
        taskQueue.put(task);
    }

    public int getServerId() {
        return serverId;
    }

    public void setServerId(int serverId) {
        this.serverId = serverId;
    }

    public int getNumberOfTasks() {
        return numberOfTasks.get();
    }

    public int getWaitingPeriod() {
        return waitingPeriod.get();
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append('\n' + "Server " + serverId + ": ");
        for(Task task : taskQueue){
            sb.append(task.toString() + " ");
        }
        return sb.toString();
    }

    public void updateWaitAndNumber(){
        int totalWait = 0, nrTasks = 0;
        for(Task task : taskQueue){
            totalWait += task.getServiceTime();
            nrTasks++;
        }

        waitingPeriod.set(totalWait);
        numberOfTasks.set(nrTasks);

    }

    public List<Integer> getWaitingPeriods(){
        return waitingPeriods;
    }

    @Override
    public void run() {
        while(running) {
            try {
                Task task = taskQueue.peek();
                if(task != null) {
                    int serviceTime = task.getServiceTime() - 1;
                    //System.out.println("Server " + serverId + " processing: " + task.toString());
                    if(serviceTime > 0){
                        task.setServiceTime(serviceTime);
                    } else {
                        taskQueue.take();
                    }
                }

                int totalWait = 0, nrTasks = 0;
                List<Task> listAux = new ArrayList<>(taskQueue);
                //System.out.print('\n' + "Server " + serverId + " queue: ");
                for(Task taskAux : listAux){
                    //System.out.print(taskAux.toString());
                    totalWait += taskAux.getServiceTime();
                    nrTasks++;
                }
                waitingPeriods.add(totalWait);

                waitingPeriod.set(totalWait);
                numberOfTasks.set(nrTasks);

                Thread.sleep(1000);

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }

    public void stop(){
        running = false;
    }

}

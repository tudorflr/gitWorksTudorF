package BusinessLogic;

import GUI.ResultFrame;
import Model.Task;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class SimulationManager implements Runnable {

    ResultFrame frame;
    public SimulationManager(ResultFrame resultFrame) {
        frame = resultFrame;
    }

    private static int id = 0;
    private int nrTasks = 0;
    private int nrServers = 0;
    private int maxTime = 0;
    private int minArrivalTime = 0;
    private int maxArrivalTime = 0;
    private int minServiceTime = 0;
    private int maxServiceTime = 0;

    private static int serviceTimeAvg = 0;

    private static StringBuilder stringBuilderFile = new StringBuilder();

    private List<Task> taskList = new ArrayList<>();
    Scheduler scheduler = new Scheduler();

    private volatile boolean running = true;
    private final AtomicInteger currentTime = new AtomicInteger(0);

    public void generateRandomTasks(int amount){

        int arrivalTime,serviceTime;
        for(int i=0;i<amount;i++){
            id++;
            arrivalTime = (int) (Math.random() * maxArrivalTime) + minArrivalTime;
            serviceTime = (int) (Math.random() * maxServiceTime) + minServiceTime;

            Task task = new Task(id, arrivalTime, serviceTime);

            taskList.add(task);
        }

    }

    public List<Task> getTaskList() {
        return taskList;
    }

    public void setSimStats(int nrTasks, int nrServers, int maxTime, int minArrivalTime, int maxArrivalTime, int minServiceTime, int maxServiceTime, String strategy) {
        this.nrTasks = nrTasks;
        this.nrServers = nrServers;
        this.maxTime = maxTime;
        this.minArrivalTime = minArrivalTime;
        this.maxArrivalTime = maxArrivalTime;
        this.minServiceTime = minServiceTime;
        this.maxServiceTime = maxServiceTime;
        scheduler.setStrategy(strategy);
    }

    public String showStats(){
        int time = currentTime.get();
        int averageWaitingTime = 0;
        averageWaitingTime = scheduler.showStats();
        averageWaitingTime = averageWaitingTime / nrServers;

        int peakTime = 0;
        peakTime = scheduler.calculatePeakHour(time);
        //System.out.println("Peak time: " + peakTime);
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Average waiting time : " + averageWaitingTime + '\n');
        stringBuilder.append("Average service time : " + serviceTimeAvg + '\n');
        stringBuilder.append("Peak time : " + peakTime + '\n');

        return stringBuilder.toString();
    }

    @Override
    public void run() {

        generateRandomTasks(nrTasks);
        scheduler.generateServers(nrServers);
        for(Task task : taskList){
            System.out.print(task.toString() + " ");
            serviceTimeAvg += task.getServiceTime();
        }
        serviceTimeAvg = serviceTimeAvg / nrTasks;

        while(running) {
            try {
                StringBuilder str = new StringBuilder();
                str.append("Time :" + currentTime.get() + "\n");
                str.append("Clients which didn't arrive : ");
                int currentTimeInt = currentTime.incrementAndGet();
                for(Task task : taskList){
                    if(task.getArrivalTime() == currentTimeInt){
                        scheduler.dispatchTask(task);
                        //taskList.remove(task);
                    }
                    if(task.getArrivalTime() > currentTimeInt){
                        str.append(task.toString() + " ");
                    }
                }

                if(currentTimeInt > maxTime){
                    scheduler.stopServers();
                    stop();
                }

                str.append("\n");
                str.append(scheduler.displayServers());

                stringBuilderFile.append("\n" + "\n");
                stringBuilderFile.append(str.toString());

                frame.setResult(str.toString());

                Thread.sleep(1000);

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }

    public void stop(){
        WriteToFile.WriteToFile(stringBuilderFile.toString());
        running = false;
    }

    public void stopServers(){
        scheduler.stopServers();
    }

}

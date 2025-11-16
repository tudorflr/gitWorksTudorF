package BusinessLogic;

import Model.Server;
import Model.Task;

import java.util.ArrayList;
import java.util.List;

public class Scheduler {

    int Strategy = 0; // 0 - time    // 1 - shortestQueue
    int maxTasksPerServer = 15;
    List<Server> servers = new ArrayList<Server>();

    public void generateServers(int amount){
        for(int i = 1; i <= amount; i++){
            Server server = new Server();
            server.setServerId(i);   // cred ca e ok
            servers.add(server);
            new Thread(server).start();
        }
    }

    public void dispatchTask(Task task) throws InterruptedException {
        if(Strategy == 0){
            TimeStrategy timeStrategy = new TimeStrategy();
            timeStrategy.addTask(servers, task);
        }
        else if(Strategy == 1){
            ShortestQueueStrategy shortestQueueStrategy = new ShortestQueueStrategy();
            shortestQueueStrategy.addTask(servers, task);
        }
    }

    public String displayServers(){
        StringBuilder str = new StringBuilder();
        for(Server server : servers){
            str.append(server.toString()); // shows their tasks too
        }
        return str.toString();
    }

    public void setStrategy(String strategy){
        if(strategy.equals("Shortest Queue")){
            Strategy = 1;
        }
        else if(strategy.equals("Shortest Time")){
            Strategy = 0;
        }
    }

    public void stopServers(){
        for(Server server : servers){
            server.stop();
        }
    }

    public int showStats(){  // for averageWaitingTime
        int finalAverageTime = 0;
        for(Server server : servers){
            List<Integer> waitingAux;
            waitingAux = server.getWaitingPeriods();
            int i = 0, averagePerServer = 0;
            for(Integer integer : waitingAux){
                averagePerServer += integer;
                i++;
            }
            averagePerServer = averagePerServer/i;
            finalAverageTime += averagePerServer;
        }
        return finalAverageTime;
    }

    public int calculatePeakHour(int time){
        int result = 0;
        for(int i = 0; i < time; i++){
            int averagePerTime = 0;
            for(Server server : servers){
                List<Integer> waitingAux;
                waitingAux = server.getWaitingPeriods();
                averagePerTime += waitingAux.get(i);
            }
            averagePerTime = averagePerTime/servers.size();
            if(averagePerTime > result){
                result = i;
            }
        }
        return result;
    }

}

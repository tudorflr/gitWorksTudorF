package BusinessLogic;

import Model.Server;
import Model.Task;

import java.util.List;

public class ShortestQueueStrategy implements Strategy {

    public void addTask(List<Server> servers, Task task) throws InterruptedException {

        int numberInQueue = 0, minQueue = Integer.MAX_VALUE, serverToAdd = 0, i = 0;
        for(Server server : servers){
            numberInQueue = server.getNumberOfTasks();
            if(minQueue > numberInQueue){
                minQueue = numberInQueue;
                serverToAdd = i;
            }
            i++;
        }

        //serverToAdd = serverToAdd - 1;
        Server server = servers.get(serverToAdd);

        server.addTask(task);
        server.updateWaitAndNumber();

    }

}

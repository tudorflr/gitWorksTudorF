package BusinessLogic;

import Model.Server;
import Model.Task;

import java.util.List;

public class TimeStrategy implements Strategy {

    public void addTask(List<Server> servers, Task task) throws InterruptedException {

        int minTime = Integer.MAX_VALUE, auxWaitingPeriod = 0, i = 0, serverToAdd = 0;

        for(Server server : servers) {

            auxWaitingPeriod = server.getWaitingPeriod();
            if(auxWaitingPeriod < minTime) {
                minTime = auxWaitingPeriod;
                serverToAdd = i;
            }
            i++;
        }

        //System.out.println(auxWaitingPeriod + " ");

        Server server = servers.get(serverToAdd);

        server.addTask(task);
        server.updateWaitAndNumber();

    }

}

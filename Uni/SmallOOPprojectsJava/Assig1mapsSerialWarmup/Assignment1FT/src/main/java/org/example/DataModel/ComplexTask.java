package org.example.DataModel;

import java.util.ArrayList;
import java.util.List;

public final class ComplexTask extends Task{
    private static final long serialVersionUID = 1L;

    private int idTask;
    private String statusTask;
    private List<Task> tasksC;

    public ComplexTask(int idTask, String statusTask){
        super(idTask, statusTask);
        this.tasksC = new ArrayList<>();
        this.idTask = idTask;
        this.statusTask = statusTask;
    }

    public void addTask(Task task){
        this.tasksC.add(task);
    }

    public void deleteTask(Task task){
        this.tasksC.remove(task);
    }

    public int getIdTask(){
        return idTask;
    }

    public List<Task> getSubTasks() {
        return tasksC;
    }

    @Override
    public int estimateDuration(){

        return 0; // de modif
    }

}

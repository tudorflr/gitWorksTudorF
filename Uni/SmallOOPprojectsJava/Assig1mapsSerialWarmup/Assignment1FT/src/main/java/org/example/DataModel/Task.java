package org.example.DataModel;

import java.io.Serializable;

public sealed abstract class Task implements Serializable permits SimpleTask, ComplexTask {
    private static final long serialVersionUID = 1L;

    private int idTask;
    private String statusTask;

    public Task(int idTask, String statusTask) {
        this.idTask = idTask;
        this.statusTask = statusTask;
    }

    public int getIdTask() {
        return idTask;
    }

    public String getStatusTask() {
        return statusTask;
    }

    public void setStatusTask(String statusTask) {
        this.statusTask = statusTask;
    }

    public abstract int estimateDuration();

}

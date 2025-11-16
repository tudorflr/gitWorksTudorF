package org.example.DataModel;

public final class SimpleTask extends Task{
    private static final long serialVersionUID = 1L;


    //private int idTask;
    //private String taskName;
    private int startHour;
    private int endHour;

    public SimpleTask(int idTask, String statusTask, int startHour, int endHour) {
        super(idTask, statusTask);
        this.startHour = startHour;
        this.endHour = endHour;
    }

    @Override
    public int estimateDuration(){
        return endHour - startHour;
    }

}

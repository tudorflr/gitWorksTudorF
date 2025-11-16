package org.example;

import org.example.DataAccess.LoadData;
import org.example.BusinessLogic.ControllerGUI;
import org.example.BusinessLogic.TaskManagement;
import org.example.GUI.ProjectManagerView;
import org.example.GUI.WelcomeView;

import java.io.IOException;

public class Main {

    private static final String DATA_FILE = "tasks_management.dat";

    public static void main(String[] args) {


        TaskManagement taskManagement = loadDataSub();


        WelcomeView welcomeView = new WelcomeView();
        ProjectManagerView projectManagerView = new ProjectManagerView();

        ControllerGUI controllerGUI = new ControllerGUI(welcomeView, projectManagerView, taskManagement);

        addShutdownHook(taskManagement);

    }

    private static TaskManagement loadDataSub() {
        TaskManagement taskManagement = (TaskManagement) LoadData.deserializeObj(DATA_FILE);

        if (taskManagement == null) {
            System.out.println("No existing data found. Creating new TasksManagement object.");
            taskManagement = new TaskManagement();
        }

        return taskManagement;
    }

    private static void addShutdownHook(TaskManagement taskManagement) {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.out.println("Serializing data to " + DATA_FILE);
            LoadData.serializeObj(taskManagement, DATA_FILE);
        }));
    }

}
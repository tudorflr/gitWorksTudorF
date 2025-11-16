package org.example.BusinessLogic;

import org.example.DataModel.Task;
import org.example.GUI.ProjectManagerView;
import org.example.GUI.ResultView;
import org.example.GUI.WelcomeView;
import org.example.BusinessLogic.Utility;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class ControllerGUI {

    private WelcomeView welcomeView;
    private ProjectManagerView projectManagerView;
    private TaskManagement taskManagement;
    private ResultView resultView;

    public ControllerGUI(WelcomeView welcomeView, ProjectManagerView projectManagerView, TaskManagement taskManagement) {
        this.welcomeView = welcomeView;
        this.projectManagerView = projectManagerView;
        this.taskManagement = taskManagement;
        this.resultView = new ResultView();

        // de sters
        //Utility utility = new Utility();
        //utility.sortEmployeeByWork(taskManagement);
        //


        welcomeView.setButtonActionListener(new CalculatorListener());
        welcomeView.setVisible(true);

        projectManagerView.setButtonActionListenerEmp(new ListenerAddEmployee());
        projectManagerView.setButtonActionListenerTask(new ListenerAddTask());
        projectManagerView.setButtonActionListenerShowTasks(new ListenerShowTasks());
        projectManagerView.setButtonActionListenerShowEmployee(new ListenerShowEmployees());
        projectManagerView.setButtonActionListenerAssignTask(new ListenerAssignTask());
        projectManagerView.setButtonActionListenerShowEmpTask(new ListenerShowTaskEmp());
        projectManagerView.setButtonActionListenerCT(new ListenerCT());
        projectManagerView.setButtonActionListenerStatus(new ListenerChangeStatus());
        projectManagerView.setButtonActionListenerCalculateWork(new ListenerCalculateWork());
        projectManagerView.setButtonActionListenerUtilityWork(new ListenerWorkAmmountDescending());
        projectManagerView.setButtonActionListenerUtilityTasksStatusEmp(new ListenerTasksStatusEmp());

        resultView.setButtonActionListenerReturn(new ListenerResultReturn());

    }

    private class CalculatorListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            welcomeView.setVisible(false);
            projectManagerView.setVisible(true);
        }
    }

    private class ListenerAddEmployee implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            taskManagement.addEmployee(projectManagerView.getEmployeeID(), projectManagerView.getEmployeeName());
        }
    }

    private class ListenerAddTask implements ActionListener {    // trb sa modif pt start si end la task
        public void actionPerformed(ActionEvent e) {
            taskManagement.addTask(projectManagerView.getTaskID(), projectManagerView.getTaskType(), projectManagerView.getTaskStartTime(), projectManagerView.getTaskEndTime());
        }
    }

    private class ListenerAssignTask implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            taskManagement.assignTaskToEmployee(projectManagerView.getTaskAssignEmpID(), projectManagerView.getTaskAssignTaskID());
        }
    }

    private class ListenerCT implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            taskManagement.modifyComplexTask(projectManagerView.getCT(), projectManagerView.getCTSecond());
        }
    }

    private class ListenerChangeStatus implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            taskManagement.modifyTaskStatus(projectManagerView.getModifyStatusInt());
        }
    }

    private class ListenerShowTasks implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            resultView.setResult(taskManagement.showAllTasks());
            projectManagerView.setVisible(false);
            resultView.setVisible(true);
        }
    }

    private class ListenerShowEmployees implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            resultView.setResult(taskManagement.showAllEmployees());
            projectManagerView.setVisible(false);
            resultView.setVisible(true);
        }
    }

    private class ListenerResultReturn implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            resultView.setVisible(false);    // buton pt return in meniu
            projectManagerView.setVisible(true);
        }
    }

    private class ListenerShowTaskEmp implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            resultView.setResult(taskManagement.showTasksforEmployee(projectManagerView.getShowTaskAssignEmpID()));
            projectManagerView.setVisible(false);
            resultView.setVisible(true);
        }
    }

    private class ListenerCalculateWork implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            resultView.setResult(taskManagement.calculateEmployeeWorkDuration(projectManagerView.getCalculateWork()));
            projectManagerView.setVisible(false);
            resultView.setVisible(true);
        }
    }

    private class ListenerWorkAmmountDescending implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Utility utility = new Utility();
            resultView.setResult(utility.sortEmployeeByWork(taskManagement));
            projectManagerView.setVisible(false);
            resultView.setVisible(true);
        }
    }

    private class ListenerTasksStatusEmp implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Utility utility = new Utility();

            Map<String, Map<String, Integer>> empNameMap = new HashMap<>();
            Map<String, Integer> empTasksAmmount = new HashMap<>();

            empNameMap = utility.employeeCompletedUn(taskManagement);

            String empName = null, status = null;
            int uncompletedTasks = 0, completedTasks = 0;
            StringBuilder stringBuilder = new StringBuilder();

            for (Map.Entry<String, Map<String, Integer>> entry : empNameMap.entrySet()) {
                empName = entry.getKey();
                Map<String, Integer> taskCounts = entry.getValue();

                completedTasks = taskCounts.getOrDefault("Completed", 0);
                uncompletedTasks = taskCounts.getOrDefault("Uncompleted", 0);

                stringBuilder.append(empName)
                        .append(": C").append(completedTasks)
                        .append(", U").append(uncompletedTasks)
                        .append("\n");
            }

            resultView.setResult(stringBuilder.toString());
            projectManagerView.setVisible(false);
            resultView.setVisible(true);

        }
    }

}

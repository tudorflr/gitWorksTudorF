package org.example.GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class ProjectManagerView extends JFrame {

    private final JLabel employeeInfo;
    private final JLabel emptyLabel1;
    private final JLabel emptyLabel2;
    private final JLabel emptyLabel3;
    private final JLabel smileLabel;

    private final JLabel employeeAddLabel;
    private final JTextField employeeAddIDText;
    private final JTextField employeeAddText;
    private final JButton employeeAddButton;

    private final JLabel taskAddLabel;
    private final JTextField taskAddIDText;
    private final JTextField taskAddTypeText;
    private final JButton taskAddButton;
    private final JLabel taskAddStartTimeLabel;
    private final JTextField taskAddStartTimeText;
    private final JLabel taskAddEndTimeLabel;
    private final JTextField taskAddEndTimeText;

    private final JLabel modifyCTLabel;
    private final JTextField modifyCTText;
    private final JTextField modifyCTsecondText;
    private final JButton modifyCTButton;

    private final JLabel assignTaskLabel;
    private final JTextField assignTaskEmpText;
    private final JTextField assignTaskTskText;
    private final JButton assignTaskButton;

    private final JTextField modifyStatusText;
    private final JButton modifyStatusButton;
    private final JTextField calculateEmployeeText;
    private final JButton calculateEmployeeButton;

    private final JButton showAllTasksButton;
    private final JButton showEmployeeButton;
    private final JTextField showTaskAssignEmpText;
    private final JButton showTaskAssignEmpButton;

    private final JLabel utilityWorkLabel;
    private final JButton utilityWorkButton;
    private final JButton utilityTaskAmmountButton;
    private final JLabel utilityTaskAmmountLabel;

    public ProjectManagerView() {
        employeeInfo = new JLabel("Employee/Task", SwingConstants.RIGHT);
        emptyLabel1 = new JLabel("      ");
        emptyLabel2 = new JLabel("  manager    ");
        emptyLabel3 = new JLabel("      ");
        smileLabel = new JLabel(" (^.^) ", SwingConstants.CENTER);

        employeeAddLabel = new JLabel("<html>Employee add : <br>  id: name: </html>" , SwingConstants.CENTER);
        employeeAddIDText = new JTextField();
        employeeAddText = new JTextField();
        employeeAddButton = new JButton("Add Employee");

        taskAddLabel = new JLabel("<html>Task add : <br>  id: type (1/2) : </html>" , SwingConstants.CENTER);
        taskAddIDText = new JTextField();
        taskAddTypeText = new JTextField();   // trb pus buton si de id
        taskAddButton = new JButton("Add Task");
        taskAddStartTimeLabel = new JLabel("Start Time : ", SwingConstants.CENTER);
        taskAddStartTimeText = new JTextField();
        taskAddEndTimeLabel = new JLabel("End Time : ", SwingConstants.CENTER);
        taskAddEndTimeText = new JTextField();

        modifyCTLabel = new JLabel("<html>Add Complex : <br>  main: subTask: </html>", SwingConstants.CENTER);
        modifyCTText = new JTextField();
        modifyCTsecondText = new JTextField();
        modifyCTButton = new JButton("Add Subtask");

        assignTaskLabel = new JLabel("<html>Assign Task : <br>  Emp: Task: </html>" , SwingConstants.CENTER);
        assignTaskEmpText = new JTextField();
        assignTaskTskText = new JTextField();
        assignTaskButton = new JButton("Assign Task");

        modifyStatusText = new JTextField();
        modifyStatusButton = new JButton("<html>Modify Completion <br>  <-- TaskID  </html>");
        calculateEmployeeText = new JTextField();
        calculateEmployeeButton = new JButton("<html>Calculate workload <br>  <-- EmployeeID  </html>");

        showAllTasksButton = new JButton("Show Tasks");
        showEmployeeButton = new JButton("Show Employee");
        showTaskAssignEmpText = new JTextField();
        showTaskAssignEmpButton = new JButton("<html>Show tasks <br>  <-- EmployeeID  </html>");

        utilityWorkLabel = new JLabel("  :D  ", SwingConstants.CENTER);
        utilityWorkButton = new JButton("<html>Calculate workload >40 <br> descending  </html>");
        utilityTaskAmmountButton = new JButton("<html>Calculate ammount <br> of Tasks per emp  </html>");
        utilityTaskAmmountLabel = new JLabel("  :p  ", SwingConstants.CENTER);

        setTitle("PM");
        setLayout(new GridLayout(9, 4));
        setSize(650,500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLocationRelativeTo(null);

        add(smileLabel);
        add(employeeInfo);
        add(emptyLabel2);
        add(emptyLabel3);

        add(employeeAddLabel);
        add(employeeAddIDText);
        add(employeeAddText);
        add(employeeAddButton);

        add(taskAddLabel);
        add(taskAddIDText);
        add(taskAddTypeText);
        add(taskAddButton);
        add(taskAddStartTimeLabel);
        add(taskAddStartTimeText);
        add(taskAddEndTimeLabel);
        add(taskAddEndTimeText);

        add(modifyCTLabel);
        add(modifyCTText);
        add(modifyCTsecondText);
        add(modifyCTButton);

        add(assignTaskLabel);
        add(assignTaskEmpText);
        add(assignTaskTskText);
        add(assignTaskButton);

        add(modifyStatusText);
        add(modifyStatusButton);
        add(calculateEmployeeText);
        add(calculateEmployeeButton);

        add(showAllTasksButton);
        add(showEmployeeButton);
        add(showTaskAssignEmpText);
        add(showTaskAssignEmpButton);

        add(utilityWorkLabel);
        add(utilityWorkButton);
        add(utilityTaskAmmountButton);
        add(utilityTaskAmmountLabel);

        //setVisible(true);
    }

    public int getEmployeeID() {
        return Integer.parseInt(employeeAddIDText.getText());
    }

    public String getEmployeeName() {
        return employeeAddText.getText();
    }

    public void setButtonActionListenerEmp(ActionListener actionListener){
        employeeAddButton.addActionListener(actionListener);
    }

    public int getTaskID() {
        return Integer.parseInt(taskAddIDText.getText());
    }

    public int getTaskType() {
        return Integer.parseInt(taskAddTypeText.getText());
    }

    public int getTaskStartTime(){
        return Integer.parseInt(taskAddStartTimeText.getText());
    }

    public int getTaskEndTime(){
        return Integer.parseInt(taskAddEndTimeText.getText());
    }

    public void setButtonActionListenerTask(ActionListener actionListener){
        taskAddButton.addActionListener(actionListener);
    }

    public int getCT() {
        return Integer.parseInt(modifyCTText.getText());
    }

    public int getCTSecond() {
        return Integer.parseInt(modifyCTsecondText.getText());
    }

    public void setButtonActionListenerCT(ActionListener actionListener){
        modifyCTButton.addActionListener(actionListener);
    }

    public void setButtonActionListenerAssignTask(ActionListener actionListener){
        assignTaskButton.addActionListener(actionListener);
    }

    public int getModifyStatusInt(){
        return Integer.parseInt(modifyStatusText.getText());
    }

    public void setButtonActionListenerStatus(ActionListener actionListener){
        modifyStatusButton.addActionListener(actionListener);
    }

    public void setButtonActionListenerShowTasks(ActionListener actionListener){
        showAllTasksButton.addActionListener(actionListener);
    }

    public void setButtonActionListenerShowEmployee(ActionListener actionListener){
        showEmployeeButton.addActionListener(actionListener);
    }

    public int getTaskAssignEmpID() {
        return Integer.parseInt(assignTaskEmpText.getText());
    }

    public int getTaskAssignTaskID(){
        return Integer.parseInt(assignTaskTskText.getText());
    }

    public int getShowTaskAssignEmpID(){
        return Integer.parseInt(showTaskAssignEmpText.getText());
    }

    public void setButtonActionListenerShowEmpTask(ActionListener actionListener){
        showTaskAssignEmpButton.addActionListener(actionListener);
    }

    public int getCalculateWork(){
        return Integer.parseInt(calculateEmployeeText.getText());
    }

    public void setButtonActionListenerCalculateWork(ActionListener actionListener){
        calculateEmployeeButton.addActionListener(actionListener);
    }

    public void setButtonActionListenerUtilityWork (ActionListener actionListener){
        utilityWorkButton.addActionListener(actionListener);
    }

    public void setButtonActionListenerUtilityTasksStatusEmp (ActionListener actionListener){
        utilityTaskAmmountButton.addActionListener(actionListener);
    }

}

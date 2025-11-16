package org.example.BusinessLogic;

//import org.example.Model
import org.example.DataModel.ComplexTask;
import org.example.DataModel.Employee;
import org.example.DataModel.SimpleTask;
import org.example.DataModel.Task;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class TaskManagement implements Serializable {
    private static final long serialVersionUID = 1L;


    private Map<Employee, List<Task>> employeeTask = new HashMap<>();
    private List<Employee> employees = new ArrayList<>();
    private List<Task> allTasks = new ArrayList<>();

    private static Integer result;

    public void addEmployee(int idToAdd, String nameToAdd) {
        int employeeID, ok = 1;
        for (Employee employee : employees) {
            employeeID = employee.getIdEmployee();   // daca se poate
            if(employeeID == idToAdd) {
                ok = 0;
            }
        }

        if(ok == 1) {
            Employee newEmployee = new Employee(idToAdd, nameToAdd);
            employees.add(newEmployee);
            employeeTask.put(newEmployee, new ArrayList<>());
        }

    }

    public void addTask(int taskID,  int taskType, int startH, int endH){ // 1 - simple // 2 - complex
        if(taskType == 1) {
            SimpleTask simpleTask = new SimpleTask(taskID, "Uncompleted", startH, endH); // vreau unu general si dupa
            allTasks.add(simpleTask);                            // sa clasific si grupez
        } else if(taskType == 2) {
            ComplexTask complexTask = new ComplexTask(taskID, "Uncompleted");
            allTasks.add(complexTask);
        }
    }

    public void modifyComplexTask(int taskID, int taskToTie){
        ComplexTask auxTask = null;
        Task auxToTieTask;
        for(Task task : allTasks) {
            if(taskID == task.getIdTask()){
                auxTask = (ComplexTask) task;
                break;
            }
        }

        for(Task task : allTasks) {
            if(taskToTie == task.getIdTask()){
                auxToTieTask = task;
                auxTask.addTask(auxToTieTask);
                break;
            }
        }

    }

    public String showAllTasks() {
        StringBuilder result = new StringBuilder();
        for (Task task : allTasks) {
            result.append(task.getIdTask()).append(" ").append(task.getStatusTask()).append('\n');
        }
        return result.toString();
    }


    public String showAllEmployees(){
        StringBuilder result = new StringBuilder();
        for(Employee employee : employees) {
            result.append(employee.getIdEmployee()).append(" ").append(employee.getNameEmployee()).append('\n');
        }
        return result.toString();
    }

    public void assignTaskToEmployee(int employeeID, int taskID) {
        Employee employeeFound = null;
        Task taskFound = null;
        for(Employee employee : employees) {
            if(employee.getIdEmployee() == employeeID) {
                employeeFound = employee;
                break;
            }
        }

        for(Task task : allTasks) {
            if(taskID == task.getIdTask()) {
                taskFound = task;
                break;
            }
        }

        employeeTask.get(employeeFound).add(taskFound);

        // employeeTask.computeIfAbsent(employeeFound, k -> new ArrayList<>()).add(taskFound);

    }

    public void modifyTaskStatus(int taskID){
        for(Task task : allTasks) {
            if(taskID == task.getIdTask()) {
                task.setStatusTask("Completed");
                break;
            }
        }
    }

    public String showTasksforEmployee(int employeeID) {
        StringBuilder result = new StringBuilder();

        Employee targetEmployee = null;
        for (Employee employee : employees) {
            if (employee.getIdEmployee() == employeeID) {
                targetEmployee = employee;
                break;
            }
        }
        result.append(targetEmployee.getIdEmployee())
                .append(" ")
                .append(targetEmployee.getNameEmployee())
                .append("\n");

        List<Task> tasks = employeeTask.get(targetEmployee);

        for(Task task : tasks) {
            result.append(task.getIdTask()).append(" ").append(task.getStatusTask()).append('\n');
            if(task instanceof ComplexTask) {
                appendSubTasks(result, (ComplexTask) task, "  -> ");
            }
        }

        return result.toString();
    }
           //  for showing tasks assigned to employee
    private void appendSubTasks(StringBuilder result, ComplexTask complexTask, String indent) {
        for(Task subTask : complexTask.getSubTasks()) {
            result.append(indent).append(subTask.getIdTask()).append(" ").append(subTask.getStatusTask()).append('\n');
            if(subTask instanceof ComplexTask) {
                appendSubTasks(result, (ComplexTask) subTask, indent + "  -> ");
            }
        }
    }

    public String calculateEmployeeWorkDuration(int employeeID){
        result = 0;

        Employee targetEmployee = null;
        for (Employee employee : employees) {
            if (employee.getIdEmployee() == employeeID) {
                targetEmployee = employee;
                break;
            }
        }

        List<Task> tasks = employeeTask.get(targetEmployee);

        for(Task task : tasks) {
            if(task instanceof SimpleTask) {
                result = result + task.estimateDuration();
            }
            if(task instanceof ComplexTask) {
                calculateSubTasks((ComplexTask) task);
            }
        }

        return result.toString();
    }

    private void calculateSubTasks(ComplexTask complexTask) {
        for(Task subTask : complexTask.getSubTasks()) {
            if(subTask instanceof SimpleTask){
                result = result + subTask.estimateDuration();
            }
            if(subTask instanceof ComplexTask) {
                calculateSubTasks((ComplexTask) subTask);
            }
        }
    }

    public List<Employee> getEmployeeList(){
        return employees;
    }

    public Map<Employee, List<Task>> getEmployeeTaskMap(){
        return employeeTask;
    }

}

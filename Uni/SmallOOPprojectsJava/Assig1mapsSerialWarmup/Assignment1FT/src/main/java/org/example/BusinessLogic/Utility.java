package org.example.BusinessLogic;

import org.example.BusinessLogic.TaskManagement;
import org.example.DataModel.ComplexTask;
import org.example.DataModel.Employee;
import org.example.DataModel.SimpleTask;
import org.example.DataModel.Task;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Utility {

    public static Integer uncompletedTasks;
    public static Integer completedTasks;

    public String sortEmployeeByWork(TaskManagement taskManagement) {
        String empWorkString = null;
        StringBuilder resultString = new StringBuilder();
        int empId, empWorkInt, i = 0;
        int workArr[] = new int[100];
        int sortedArr[] = new int[100];


        List<Employee> employeeList = taskManagement.getEmployeeList();
        List<Employee> employeeWithWork = new ArrayList<Employee>();

        for(Employee employee : employeeList) {
            empId = employee.getIdEmployee();
            empWorkString = taskManagement.calculateEmployeeWorkDuration(empId);
            empWorkInt = Integer.parseInt(empWorkString);
            if(empWorkInt > 40) {
                employeeWithWork.add(employee);
                workArr[i] = empWorkInt;
                i++;
            }
        }

        for(int j = 0; j < i; j++){
            sortedArr[j] = j;
        }

        for(int j = 1; j < i; j++){
            for(int k = 1; k < i; k++){
                if(workArr[k] > workArr[k - 1]){
                    int aux;
                    aux = workArr[k];
                    workArr[k] = workArr[k - 1]; // asta a fost un challange
                    workArr[k - 1] = aux;        // in loc sa adaug field de
                    aux = sortedArr[k];          // workLoad in emp si sa fac sort simplu
                    sortedArr[k] = sortedArr[k - 1];
                    sortedArr[k - 1] = aux;
                }
            }
        }

        for(int j = 0; j < i; j++){
            Employee employeeAux;
            employeeAux = employeeWithWork.get(sortedArr[j]);

            resultString.append(employeeAux.getNameEmployee());
            resultString.append("\n");
        }

        return resultString.toString();
    }

    public  Map<String, Map<String, Integer>> employeeCompletedUn(TaskManagement taskManagement) {

        String empName = null, taskStatus = null;
        Map<String, Map<String, Integer>> empNameMap = new HashMap<>();
        //Map<String, Integer> empTasksAmmount = new HashMap<>();

        Map<Employee, List<Task>> employeeTasksMap = new HashMap<>();
        employeeTasksMap = taskManagement.getEmployeeTaskMap();

        for(Employee employee : employeeTasksMap.keySet()) {
            empName = employee.getNameEmployee();

            List<Task> tasks = employeeTasksMap.get(employee);
            Map<String, Integer> empTasksAmmount = new HashMap<>();

            uncompletedTasks = 0;
            completedTasks = 0;

            for(Task task : tasks) {
                String statusAux = null;
                statusAux = task.getStatusTask();
                if(statusAux.equals("Completed")) {
                    completedTasks++;
                } else {
                    uncompletedTasks++;
                }
                if(task instanceof ComplexTask) {
                    calculateSubTasks((ComplexTask) task);
                }
            }

            //System.out.println(empName + " " + completedTasks + " " + uncompletedTasks);
            empTasksAmmount.put("Uncompleted", uncompletedTasks);
            empTasksAmmount.put("Completed", completedTasks);
            empNameMap.put(empName, empTasksAmmount);

        }

        return empNameMap;
    }

    private void calculateSubTasks(ComplexTask complexTask) {
        for(Task subTask : complexTask.getSubTasks()) {
            String statusAux = null;
            statusAux = subTask.getStatusTask();
            if(statusAux.equals("Completed")) {
                completedTasks++;
            } else {
                uncompletedTasks++;
            }
            if(subTask instanceof ComplexTask) {
                calculateSubTasks((ComplexTask) subTask);
            }
        }
    }

}

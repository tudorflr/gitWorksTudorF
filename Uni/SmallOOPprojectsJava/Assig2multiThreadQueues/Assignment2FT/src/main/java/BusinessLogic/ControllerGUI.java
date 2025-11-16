package BusinessLogic;

import GUI.ResultFrame;
import GUI.SetupFrame;
import GUI.SimulationFrame;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ControllerGUI {

    private ResultFrame resultFrame = new ResultFrame();
    private SetupFrame setupFrame = new SetupFrame();
    private SimulationFrame simulationFrame = new SimulationFrame();

    //SimulationManager simulationManager = new SimulationManager(resultFrame);
    SimulationManager simulationManager;

    public ControllerGUI() {

        simulationFrame.setVisible(true);

        simulationFrame.setButtonActionListenerSetup(new ListenerSimulationSim());
        simulationFrame.setButtonActionListenerStart(new ListenerSimulationRes());
        simulationFrame.setButtonActionListenerStatistics(new ListenerSimulationStat());
        setupFrame.setButtonActionListenerSave(new ListenerSetup());
        resultFrame.setButtonActionListenerReturn(new ListenerResult());

    }

    private class ListenerSimulationSim implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            simulationFrame.setVisible(false);
            SimulationManager simulationManagerNew = new SimulationManager(resultFrame);
            simulationManager = simulationManagerNew;
            setupFrame.setVisible(true);
        }
    }

    private class ListenerSetup implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            setupFrame.setVisible(false);
            simulationManager.setSimStats(setupFrame.getNrTasks(), setupFrame.getNrServers(), setupFrame.getMaxSimulationTime(), setupFrame.getMinArrivalTime(), setupFrame.getMaxArrivalTime(), setupFrame.getMinServiceTime(), setupFrame.getMaxServiceTime(), setupFrame.getStrategy());
            simulationFrame.setVisible(true);
        }
    }

    private class ListenerResult implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            resultFrame.setVisible(false);
            simulationManager.stopServers();
            simulationManager.stop();
            simulationFrame.setVisible(true);
        }
    }

    private class ListenerSimulationRes implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            setupFrame.setVisible(false);
            new Thread(simulationManager).start();
            resultFrame.setVisible(true);
        }
    }

    private class ListenerSimulationStat implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            setupFrame.setVisible(false);
            String result;
            result = simulationManager.showStats();
            resultFrame.setResult(result);
            resultFrame.setVisible(true);
        }
    }

}

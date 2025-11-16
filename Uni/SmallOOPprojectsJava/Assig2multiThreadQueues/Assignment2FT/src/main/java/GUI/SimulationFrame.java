package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class SimulationFrame extends JFrame {

    private final JButton setupSim;
    private final JButton startSim;
    private final JButton viewStatistics;

    public SimulationFrame() {

        setTitle("main");
        setSize(400, 300);
        setLayout(new GridLayout(3, 1));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);


        setupSim = new JButton("Setup");
        startSim = new JButton("Start");
        viewStatistics = new JButton("View");


        add(setupSim);
        add(startSim);
        add(viewStatistics);


    }

    public void setButtonActionListenerSetup(ActionListener actionListener) {
        setupSim.addActionListener(actionListener);
    }

    public void setButtonActionListenerStart(ActionListener actionListener) {
        startSim.addActionListener(actionListener);
    }

    public void setButtonActionListenerStatistics(ActionListener actionListener) {
        viewStatistics.addActionListener(actionListener);
    }

}

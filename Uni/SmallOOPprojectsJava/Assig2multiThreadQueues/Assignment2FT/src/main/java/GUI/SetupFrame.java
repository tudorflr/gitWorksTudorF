package GUI;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionListener;

public class SetupFrame extends JFrame {

    private final JLabel startLabel;
    private final JButton endButton;
    private final JTable paramTable;
    private final JComboBox<String> strategyComboBox;

    public SetupFrame() {
        startLabel = new JLabel("Simulation Setup", SwingConstants.CENTER);
        startLabel.setFont(new Font("Arial", Font.BOLD, 16));

        endButton = new JButton("Save");
        strategyComboBox = new JComboBox<>(new String[]{"Shortest Queue", "Shortest Time"});

        // Create table with parameters
        String[] columns = {"Parameter", "Value"};
        Object[][] data = {
                {"Number of Tasks", "10"},
                {"Number of Servers", "2"},
                {"Max Simulation Time", "30"},
                {"Min Arrival Time", "1"},
                {"Max Arrival Time", "10"},
                {"Min Service Time", "1"},
                {"Max Service Time", "10"}
        };
        DefaultTableModel model = new DefaultTableModel(data, columns);
        paramTable = new JTable(model);

        paramTable.setRowHeight(25);
        paramTable.getColumnModel().getColumn(1).setCellEditor(new DefaultCellEditor(new JTextField()));

        setTitle("Simulation Setup");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel mainPanel = new JPanel(new BorderLayout(10, 10));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        mainPanel.add(startLabel, BorderLayout.NORTH);

        JPanel centerPanel = new JPanel(new BorderLayout());
        centerPanel.add(new JScrollPane(paramTable), BorderLayout.CENTER);

        JPanel strategyPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        strategyPanel.add(new JLabel("Strategy:"));
        strategyPanel.add(strategyComboBox);
        centerPanel.add(strategyPanel, BorderLayout.SOUTH);

        mainPanel.add(centerPanel, BorderLayout.CENTER);
        mainPanel.add(endButton, BorderLayout.SOUTH);

        add(mainPanel);

    }

    public void setButtonActionListenerSave(ActionListener actionListener) {
        endButton.addActionListener(actionListener);
    }

    public int getNrTasks(){
        return Integer.parseInt(paramTable.getValueAt(0, 1).toString());
    }

    public int getNrServers(){
        return Integer.parseInt(paramTable.getValueAt(1, 1).toString());
    }

    public int getMaxSimulationTime(){
        return Integer.parseInt(paramTable.getValueAt(2, 1).toString());
    }

    public int getMinArrivalTime(){
        return Integer.parseInt(paramTable.getValueAt(3, 1).toString());
    }

    public int getMaxArrivalTime(){
        return Integer.parseInt(paramTable.getValueAt(4, 1).toString());
    }

    public int getMinServiceTime(){
        return Integer.parseInt(paramTable.getValueAt(5, 1).toString());
    }

    public int getMaxServiceTime(){
        return Integer.parseInt(paramTable.getValueAt(6, 1).toString());
    }

    public String getStrategy(){
        return strategyComboBox.getSelectedItem().toString();
    }

}
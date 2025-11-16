package presentation;

import model.Orders;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class OrderView extends JFrame {
    private final Map<String, JTextField> fieldMap = new HashMap<>();
    private final JButton addButton = new JButton("Add");
    private final JButton editButton = new JButton("Edit");
    private final JButton deleteButton = new JButton("Delete");
    private final JButton viewAllButton = new JButton("View All");
    private final JTable table = new JTable();
    private final JScrollPane tableScroll = new JScrollPane(table);

    public OrderView() {
        setTitle("Order Management");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 600);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        JPanel formPanel = new JPanel(new GridLayout(0, 2, 5, 5));
        for (Field field : Orders.class.getDeclaredFields()) {
            String fieldName = field.getName();
            JLabel label = new JLabel(capitalize(fieldName) + ":");
            JTextField textField = new JTextField(10);
            fieldMap.put(fieldName, textField);
            formPanel.add(label);
            formPanel.add(textField);
        }

        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(addButton);
        buttonPanel.add(editButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(viewAllButton);

        add(formPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.CENTER);
        add(tableScroll, BorderLayout.SOUTH);

        setVisible(true);
    }

    private String capitalize(String str) {
        if (str == null || str.isEmpty()) return str;
        return Character.toUpperCase(str.charAt(0)) + str.substring(1);
    }

    public String getFieldValue(String fieldName) {
        JTextField field = fieldMap.get(fieldName);
        return field != null ? field.getText() : null;
    }

    public void setFieldValue(String fieldName, String value) {
        JTextField field = fieldMap.get(fieldName);
        if (field != null) field.setText(value);
    }

    public Map<String, JTextField> getFieldMap() {
        return fieldMap;
    }

    public void addAddListener(ActionListener a) {
        addButton.addActionListener(a);
    }

    public void addEditListener(ActionListener a) {
        editButton.addActionListener(a);
    }

    public void addDeleteListener(ActionListener a) {
        deleteButton.addActionListener(a);
    }

    public void addViewAllListener(ActionListener a) {
        viewAllButton.addActionListener(a);
    }

    public void displayOrders(List<Orders> orders) {
        JTable generatedTable = TableGenerator.generateTable(orders);
        table.setModel(generatedTable.getModel());
    }
}
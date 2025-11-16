package presentation;

import model.Client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.lang.reflect.Field;
import java.util.*;
import java.util.List;

/**
 * gui window for client operations: add, edit, delete, and view all clients
 * uses reflection to dynamically generate form fields and table columns
 * other views pretty much the same didnt do comments for them too
 */

public class ClientView extends JFrame {
    private final Map<String, JTextField> fieldMap = new HashMap<>();
    private final JButton addButton = new JButton("Add");
    private final JButton editButton = new JButton("Edit");
    private final JButton deleteButton = new JButton("Delete");
    private final JButton viewAllButton = new JButton("View All");
    private final JTable table = new JTable();
    private final JScrollPane tableScroll = new JScrollPane(table);

    public ClientView() {
        setTitle("Client Management");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 600);
        setLayout(new BorderLayout());
        setLocationRelativeTo(null);

        // Dynamic form generation using reflection
        JPanel formPanel = new JPanel(new GridLayout(0, 2, 5, 5));
        for (Field field : Client.class.getDeclaredFields()) {
            String fieldName = field.getName();
            JLabel label = new JLabel(capitalize(fieldName) + ":");
            JTextField textField = new JTextField(10);
            fieldMap.put(fieldName, textField);
            formPanel.add(label);
            formPanel.add(textField);
        }

        // Buttons
        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(addButton);
        buttonPanel.add(editButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(viewAllButton);

        // Layout
        add(formPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.CENTER);
        add(tableScroll, BorderLayout.SOUTH);

        setVisible(true);
    }

    // Helper to capitalize field names
    private String capitalize(String str) {
        if (str == null || str.isEmpty()) return str;
        return Character.toUpperCase(str.charAt(0)) + str.substring(1);
    }

    // Getter to access field text values dynamically
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

    // Action listeners
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

    // Show data in table
    public void displayClients(List<Client> clients) {
        JTable generatedTable = TableGenerator.generateTable(clients);
        table.setModel(generatedTable.getModel());
    }
}
package presentation;

import model.Product;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

public class ProductView extends JFrame {
    private final Map<String, JTextField> fieldMap = new HashMap<>();
    private final JButton addButton = new JButton("Add");
    private final JButton editButton = new JButton("Edit");
    private final JButton deleteButton = new JButton("Delete");
    private final JButton viewAllButton = new JButton("View All");
    private final JTable table = new JTable();
    private final JScrollPane tableScroll = new JScrollPane(table);

    public ProductView() {
        setTitle("Product Management");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(700, 620);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        // Dynamic form generation using reflection
        JPanel formPanel = new JPanel(new GridLayout(0, 2, 5, 5));
        for (Field field : Product.class.getDeclaredFields()) {
            String fieldName = field.getName();
            JLabel label = new JLabel(capitalize(fieldName) + ":");
            JTextField textField = new JTextField(15);
            fieldMap.put(fieldName, textField);
            formPanel.add(label);
            formPanel.add(textField);
        }

        // Buttons panel
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

    public void addAddListener(ActionListener listener) {
        addButton.addActionListener(listener);
    }

    public void addEditListener(ActionListener listener) {
        editButton.addActionListener(listener);
    }

    public void addDeleteListener(ActionListener listener) {
        deleteButton.addActionListener(listener);
    }

    public void addViewAllListener(ActionListener listener) {
        viewAllButton.addActionListener(listener);
    }

    public void displayProducts(List<Product> products) {
        JTable generatedTable = TableGenerator.generateTable(products);
        table.setModel(generatedTable.getModel());
    }
}
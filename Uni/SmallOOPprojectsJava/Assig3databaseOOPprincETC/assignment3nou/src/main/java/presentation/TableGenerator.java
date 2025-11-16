package presentation;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.lang.reflect.Field;
import java.util.List;

/**
 * utility class for generating a jtable from a list of objects using reflection.
 * dynamically extracts field names for headers and fills rows with object values.
 */

public class TableGenerator {
    public static <T> JTable generateTable(List<T> objects) {
        if (objects == null || objects.isEmpty()) {
            return new JTable();
        }

        Class<?> classAux = objects.get(0).getClass();
        Field[] fields = classAux.getDeclaredFields();
        String[] columnNames = new String[fields.length];

        for (int i = 0; i < fields.length; i++) {
            columnNames[i] = fields[i].getName();
        }

        DefaultTableModel model = new DefaultTableModel(columnNames, 0);

        for (T obj : objects) {
            Object[] rowData = new Object[fields.length];
            for (int i = 0; i < fields.length; i++) {
                fields[i].setAccessible(true);
                try {
                    rowData[i] = fields[i].get(obj);
                } catch (IllegalAccessException e) {
                    rowData[i] = "N/A";
                }
            }
            model.addRow(rowData);
        }

        return new JTable(model);
    }
}
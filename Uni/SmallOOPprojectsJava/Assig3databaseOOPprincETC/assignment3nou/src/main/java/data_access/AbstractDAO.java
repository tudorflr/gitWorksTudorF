package data_access;

//import ConnectionFactory;

import java.lang.reflect.Field;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * this is a generic dao class that works with any model using reflection
 *
 * the constructor takes a class type and saves it
 *
 * insert builds a query with all fields except the id and inserts values using reflection
 *
 * update looks for the id field, uses that in the where clause, and sets every other field with new values
 *
 * delete deletes by id, just finds the field that ends with 'id' and makes a query using that
 *
 * findById finds a row by its id and uses resultSet to build an object from it
 *
 * findAll just gets everything from the table and returns a list of objects
 *
 * createObject uses reflection to fill an object with values from a resultSet
 *
 * relies on a ConnectionFactory class to get the db connection
 */

public class AbstractDAO<T> {
    private final Class<T> type;

    public AbstractDAO(Class<T> type) {
        this.type = type;
    }

    public void insert(T object) {
        StringBuilder fields = new StringBuilder();
        StringBuilder placeholders = new StringBuilder();
        List<Object> values = new ArrayList<>();

        for (Field field : type.getDeclaredFields()) {
            if (field.getName().equalsIgnoreCase("id")) continue;
            field.setAccessible(true);
            fields.append(field.getName()).append(",");
            placeholders.append("?,");
            try {
                values.add(field.get(object));
            } catch (IllegalAccessException e) {
                throw new RuntimeException("Error getting field value", e);
            }
        }

        String query = String.format("INSERT INTO %s (%s) VALUES (%s)",
                type.getSimpleName().toLowerCase(),
                fields.substring(0, fields.length() - 1),
                placeholders.substring(0, placeholders.length() - 1));

        try (Connection conn = ConnectionFactory.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            for (int i = 0; i < values.size(); i++) {
                stmt.setObject(i + 1, values.get(i));
            }

            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error inserting " + type.getSimpleName(), e);
        }
    }

    private Field getIdField() {
        for (Field field : type.getDeclaredFields()) {
            if (field.getName().toLowerCase().endsWith("id")) {
                field.setAccessible(true);
                return field;
            }
        }
        throw new RuntimeException("No ID field found in " + type.getSimpleName());
    }

    public void update(T object) {
        StringBuilder query = new StringBuilder("UPDATE ");
        query.append(type.getSimpleName().toLowerCase()).append(" SET ");
        List<Object> values = new ArrayList<>();

        Field idField = getIdField();
        Object idValue;

        try {
            idValue = idField.get(object);
        } catch (IllegalAccessException e) {
            throw new RuntimeException("Failed to access ID field", e);
        }

        for (Field field : type.getDeclaredFields()) {
            if (field.equals(idField)) continue;
            field.setAccessible(true);
            try {
                query.append(field.getName()).append("=?, ");
                values.add(field.get(object));
            } catch (IllegalAccessException e) {
                throw new RuntimeException(e);
            }
        }

        query.setLength(query.length() - 2);
        query.append(" WHERE ").append(idField.getName()).append("=?");

        try (Connection conn = ConnectionFactory.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query.toString())) {

            for (int i = 0; i < values.size(); i++) {
                stmt.setObject(i + 1, values.get(i));
            }
            stmt.setObject(values.size() + 1, idValue);
            stmt.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException("Error updating " + type.getSimpleName(), e);
        }
    }

    public void delete(int id) {
        Field idField = getIdField();
        String query = "DELETE FROM " + type.getSimpleName().toLowerCase() + " WHERE " + idField.getName() + "=?";
        try (Connection conn = ConnectionFactory.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setInt(1, id);
            stmt.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException("Error deleting " + type.getSimpleName(), e);
        }
    }

    public T findById(int id) {
        Field idField = getIdField();
        String query = "SELECT * FROM " + type.getSimpleName().toLowerCase() + " WHERE " + idField.getName() + "=?";
        try (Connection conn = ConnectionFactory.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setInt(1, id);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return createObject(rs);
            }

        } catch (SQLException e) {
            throw new RuntimeException("Error finding by ID " + type.getSimpleName(), e);
        }
        return null;
    }

    public List<T> findAll() {
        List<T> list = new ArrayList<>();
        String query = "SELECT * FROM " + type.getSimpleName().toLowerCase();
        try (Connection conn = ConnectionFactory.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                list.add(createObject(rs));
            }

        } catch (SQLException e) {
            throw new RuntimeException("Error finding all " + type.getSimpleName(), e);
        }
        return list;
    }

    private T createObject(ResultSet rs) {
        try {
            T instance = type.getDeclaredConstructor().newInstance();
            for (Field field : type.getDeclaredFields()) {
                field.setAccessible(true);
                Object val = rs.getObject(field.getName());
                field.set(instance, val);
            }
            return instance;
        } catch (Exception e) {
            throw new RuntimeException("Error creating object from result set", e);
        }
    }
}
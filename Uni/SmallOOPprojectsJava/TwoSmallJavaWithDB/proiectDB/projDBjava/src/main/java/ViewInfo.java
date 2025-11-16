import javax.swing.*;
import java.awt.*;
import java.sql.*;
import java.util.ArrayList;

public class ViewInfo extends JFrame {

    private final JLabel title;
    private final JLabel nameLabel;
    private final JLabel emailLabel;
    private final JLabel ageLabel;
    private final JLabel emptyLabel;

    private final JTextField nameField;
    private final JTextField emailField;
    private final JTextField ageField;
    private final JTextField searchField;

    private final JButton processButton;
    private final JButton finishButton;
    private final JButton updateButton;
    private final JButton deleteButton;
    private final JButton searchButton;
    private final JButton viewAllButton;

    private final JButton viewAppointmentsButton;
    private final JButton viewMembershipsButton;
    private final JButton createAppointmentButton;
    private final JButton updateAppointmentButton;
    private final JButton contributeMoneyButton;
    private final JButton manageEquipmentButton;

    private final Connection connection;

    public ViewInfo(Connection connection) {
        this.connection = connection;

        title = new JLabel("Welcome to the Tennis System");
        emptyLabel = new JLabel("");
        nameLabel = new JLabel("Name:");
        emailLabel = new JLabel("Email:");
        ageLabel = new JLabel("Age:");
        searchField = new JTextField();

        nameField = new JTextField();
        emailField = new JTextField();
        ageField = new JTextField();

        processButton = new JButton("Process");
        finishButton = new JButton("Finish");
        updateButton = new JButton("Update User");
        deleteButton = new JButton("Delete User");
        searchButton = new JButton("Search User");
        viewAllButton = new JButton("View All Users");
        viewAppointmentsButton = new JButton("View Appointments");
        viewMembershipsButton = new JButton("View Memberships");
        createAppointmentButton = new JButton("Create Appointment");
        updateAppointmentButton = new JButton("Update Appointment");
        contributeMoneyButton = new JButton("Contribute Money");
        manageEquipmentButton = new JButton("Manage Equipment Rentals");

        setTitle("Insert User Info");
        setLayout(new GridLayout(10, 2));
        setSize(400, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        add(title);
        add(emptyLabel);
        add(nameLabel);
        add(nameField);
        add(emailLabel);
        add(emailField);
        add(ageLabel);
        add(ageField);
        add(processButton);
        add(finishButton);
        add(updateButton);
        add(deleteButton);
        add(searchField);
        add(searchButton);
        add(viewAllButton);
        add(viewMembershipsButton);
        add(createAppointmentButton);
        add(updateAppointmentButton);
        add(contributeMoneyButton);
        add(manageEquipmentButton);


        setButtonActionListener();
        setButtonActionListenerFinish();
        setUpdateActionListener();
        setDeleteActionListener();
        setSearchActionListener();
        setViewAllActionListener();
        setButtonActionListenerViewMemberships(viewMembershipsButton);
        setButtonActionListenerCreateAppointment(createAppointmentButton);
        setButtonActionListenerUpdateAppointment(updateAppointmentButton);
        setButtonActionListenercontributeMoneyButton(contributeMoneyButton);
        setButtonActionListenermanageEquipmentButton(manageEquipmentButton);
    }

    public String getName() {
        return nameField.getText();
    }

    public String getEmail() {
        return emailField.getText();
    }

    public int getAge() {
        return Integer.parseInt(ageField.getText());
    }

    public String getSearchQuery() {
        return searchField.getText();
    }

    private void setButtonActionListenercontributeMoneyButton(JButton button) {
        button.addActionListener(e -> contributeMoneyAction());
    }

    private void setButtonActionListenermanageEquipmentButton(JButton button) {
        button.addActionListener(e -> manageEquipmentAction());
    }

    private void setButtonActionListenerViewMemberships(JButton button) {
        button.addActionListener(e -> viewMemberships());
    }

    private void setButtonActionListenerCreateAppointment(JButton button) {
        button.addActionListener(e -> createAppointment());
    }

    private void setButtonActionListenerUpdateAppointment(JButton button) {
        button.addActionListener(e -> updateAppointmentStatus());
    }

    public void setButtonActionListener() {
        processButton.addActionListener(e -> {
            String name = getName();
            String email = getEmail();
            int age = getAge();
            insertUserToDatabase(name, email, age);
        });
    }

    public void setButtonActionListenerFinish() {
        finishButton.addActionListener(e -> {
            System.exit(0);
        });
    }

    public void setUpdateActionListener() {
        updateButton.addActionListener(e -> {
            String name = getName();
            String email = getEmail();
            int age = getAge();
            updateUserInfo(name, email, age);
        });
    }

    public void setDeleteActionListener() {
        deleteButton.addActionListener(e -> {
            String name = getName();
            deleteUser(name);
        });
    }

    // Action listener for "Search" button
    public void setSearchActionListener() {
        searchButton.addActionListener(e -> {
            String query = getSearchQuery();
            searchUser(query);
        });
    }

    // Action listener for "View All Users" button
    public void setViewAllActionListener() {
        viewAllButton.addActionListener(e -> {
            viewAllUsers();
        });
    }

    private void insertUserToDatabase(String name, String email, int age) {
        String insertQuery = "INSERT INTO Users (username, email, password, full_name, phone_number) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(insertQuery)) {
            preparedStatement.setString(1, name);
            preparedStatement.setString(2, email);
            preparedStatement.setString(3, "defaultpassword");
            preparedStatement.setString(4, name);
            preparedStatement.setString(5, "1234567890");
            int rowsAffected = preparedStatement.executeUpdate();

            if (rowsAffected > 0) {
                JOptionPane.showMessageDialog(this, "User added successfully!");
            } else {
                JOptionPane.showMessageDialog(this, "Failed to add user.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void updateUserInfo(String name, String email, int age) {
        String updateQuery = "UPDATE Users SET email = ?, full_name = ? WHERE username = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(updateQuery)) {
            preparedStatement.setString(1, email);
            preparedStatement.setString(2, name);
            preparedStatement.setString(3, name);
            int rowsAffected = preparedStatement.executeUpdate();

            if (rowsAffected > 0) {
                JOptionPane.showMessageDialog(this, "User updated successfully!");
            } else {
                JOptionPane.showMessageDialog(this, "User not found.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void deleteUser(String name) {
        String deleteQuery = "DELETE FROM Users WHERE username = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(deleteQuery)) {
            preparedStatement.setString(1, name);
            int rowsAffected = preparedStatement.executeUpdate();

            if (rowsAffected > 0) {
                JOptionPane.showMessageDialog(this, "User deleted successfully!");
            } else {
                JOptionPane.showMessageDialog(this, "User not found.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void searchUser(String query) {
        String searchQuery = "SELECT * FROM Users WHERE username LIKE ? OR email LIKE ? OR phone_number LIKE ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(searchQuery)) {
            preparedStatement.setString(1, "%" + query + "%");
            preparedStatement.setString(2, "%" + query + "%");
            preparedStatement.setString(3, "%" + query + "%");

            ResultSet resultSet = preparedStatement.executeQuery();
            ArrayList<String> users = new ArrayList<>();
            while (resultSet.next()) {
                String userInfo = "ID: " + resultSet.getInt("user_id") + ", Name: " + resultSet.getString("username") +
                        ", Email: " + resultSet.getString("email") + ", Phone: " + resultSet.getString("phone_number");
                users.add(userInfo);
            }
            if (users.isEmpty()) {
                JOptionPane.showMessageDialog(this, "No user found.");
            } else {
                JOptionPane.showMessageDialog(this, "Search Results:\n" + String.join("\n", users));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }


    private void viewAllUsers() {
        String viewQuery = "SELECT * FROM Users";
        try (PreparedStatement preparedStatement = connection.prepareStatement(viewQuery)) {
            ResultSet resultSet = preparedStatement.executeQuery();
            ArrayList<String> users = new ArrayList<>();
            while (resultSet.next()) {
                String userInfo = "ID: " + resultSet.getInt("user_id") + ", Name: " + resultSet.getString("username") +
                        ", Email: " + resultSet.getString("email");
                users.add(userInfo);
            }
            if (users.isEmpty()) {
                JOptionPane.showMessageDialog(this, "No users found.");
            } else {
                JOptionPane.showMessageDialog(this, "All Users:\n" + String.join("\n", users));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void viewMemberships() {
        String query = "SELECT * FROM Memberships";
        try (Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(query)) {
            ArrayList<String> memberships = new ArrayList<>();
            while (resultSet.next()) {
                String membership = "ID: " + resultSet.getInt("membership_id") + ", User ID: " + resultSet.getInt("user_id") +
                        ", Type: " + resultSet.getString("membership_type") + ", Start Date: " + resultSet.getDate("start_date") +
                        ", End Date: " + resultSet.getDate("end_date");
                memberships.add(membership);
            }
            if (memberships.isEmpty()) {
                JOptionPane.showMessageDialog(this, "No memberships found.");
            } else {
                JOptionPane.showMessageDialog(this, "Memberships:\n" + String.join("\n", memberships));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void createAppointment() {
        String userId = JOptionPane.showInputDialog("Enter User ID:");
        String courtId = JOptionPane.showInputDialog("Enter Court ID:");
        String coachId = JOptionPane.showInputDialog("Enter Coach ID (optional):");
        String date = JOptionPane.showInputDialog("Enter Appointment Date (YYYY-MM-DD):");
        String startTime = JOptionPane.showInputDialog("Enter Start Time (HH:MM):");
        String endTime = JOptionPane.showInputDialog("Enter End Time (HH:MM):");

        String query = "INSERT INTO Appointments (user_id, court_id, coach_id, appointment_date, start_time, end_time) VALUES (?, ?, ?, ?, ?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setInt(1, Integer.parseInt(userId));
            preparedStatement.setInt(2, Integer.parseInt(courtId));
            preparedStatement.setObject(3, coachId.isEmpty() ? null : Integer.parseInt(coachId));
            preparedStatement.setDate(4, Date.valueOf(date));
            preparedStatement.setTime(5, Time.valueOf(startTime + ":00"));
            preparedStatement.setTime(6, Time.valueOf(endTime + ":00"));

            preparedStatement.executeUpdate();
            JOptionPane.showMessageDialog(this, "Appointment Created Successfully!");
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void updateAppointmentStatus() {
        String appointmentId = JOptionPane.showInputDialog("Enter Appointment ID to Update:");
        String newStatus = JOptionPane.showInputDialog("Enter New Status (Scheduled, Completed, Cancelled):");

        String query = "UPDATE Appointments SET status = ? WHERE appointment_id = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, newStatus);
            preparedStatement.setInt(2, Integer.parseInt(appointmentId));

            preparedStatement.executeUpdate();
            JOptionPane.showMessageDialog(this, "Appointment Status Updated Successfully!");
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void contributeMoneyAction() {
        try {
            String name = JOptionPane.showInputDialog("Enter the user's name:");

            String query = "SELECT u.user_id, u.username, m.membership_type FROM Users u " +
                    "LEFT JOIN Memberships m ON u.user_id = m.user_id WHERE u.username = ?";

            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, name);
                ResultSet resultSet = preparedStatement.executeQuery();

                if (resultSet.next()) {
                    int userId = resultSet.getInt("user_id");
                    String username = resultSet.getString("username");
                    String membershipType = resultSet.getString("membership_type");

                    JOptionPane.showMessageDialog(this,
                            "User: " + username + "\nCurrent Membership: " +
                                    (membershipType != null ? membershipType : "None"));

                    int upgradeCost = 0;
                    String newMembership = null;

                    if ("Basic".equalsIgnoreCase(membershipType)) {
                        upgradeCost = 200;
                        newMembership = "Premium";
                    } else if ("Premium".equalsIgnoreCase(membershipType)) {
                        upgradeCost = 500;
                        newMembership = "VIP";
                    } else if (membershipType == null) {
                        upgradeCost = 100; // Assign cost for creating a new membership
                        newMembership = "Basic";
                    } else {
                        JOptionPane.showMessageDialog(this, "No upgrades available for VIP.");
                        return;
                    }

                    int confirm = JOptionPane.showConfirmDialog(this,
                            "Upgrade to " + newMembership + " for $" + upgradeCost + "?",
                            "Confirm Upgrade", JOptionPane.YES_NO_OPTION);

                    if (confirm == JOptionPane.YES_OPTION) {
                        String updateQuery;
                        if (membershipType == null) {
                            updateQuery = "INSERT INTO Memberships (user_id, membership_type, start_date, end_date) " +
                                    "VALUES (?, ?, CURRENT_DATE, CURRENT_DATE + INTERVAL '1 year')";
                        } else {
                            updateQuery = "UPDATE Memberships SET membership_type = ?, start_date = CURRENT_DATE, " +
                                    "end_date = CURRENT_DATE + INTERVAL '1 year' WHERE user_id = ?";
                        }

                        try (PreparedStatement updateStmt = connection.prepareStatement(updateQuery)) {
                            if (membershipType == null) {
                                updateStmt.setInt(1, userId); // user_id for insert
                                updateStmt.setString(2, newMembership); // membership_type for insert
                            } else {
                                updateStmt.setString(1, newMembership); // membership_type for update
                                updateStmt.setInt(2, userId); // user_id for update
                            }

                            updateStmt.executeUpdate();
                            JOptionPane.showMessageDialog(this, "Membership upgraded successfully to " + newMembership + "!");
                        }
                    }
                } else {
                    JOptionPane.showMessageDialog(this, "No user found with the name: " + name);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void manageEquipmentAction() {
        try {
            String query = "SELECT equipment_id, name, equipment_type, available_quantity FROM Equipment WHERE available_quantity > 0";
            StringBuilder equipmentList = new StringBuilder("Available Equipment:\n\n");

            try (Statement statement = connection.createStatement();
                 ResultSet resultSet = statement.executeQuery(query)) {
                while (resultSet.next()) {
                    int equipmentId = resultSet.getInt("equipment_id");
                    String name = resultSet.getString("name");
                    String type = resultSet.getString("equipment_type");
                    int quantity = resultSet.getInt("available_quantity");

                    equipmentList.append("ID: ").append(equipmentId)
                            .append(", Name: ").append(name)
                            .append(", Type: ").append(type)
                            .append(", Quantity: ").append(quantity).append("\n");
                }
            }

            JOptionPane.showMessageDialog(this, equipmentList.length() > 0 ? equipmentList.toString() : "No equipment available.");

            String userName = JOptionPane.showInputDialog("Enter the user's name:");

            String userQuery = "SELECT user_id FROM Users WHERE username = ?";
            int userId = -1;
            try (PreparedStatement userStmt = connection.prepareStatement(userQuery)) {
                userStmt.setString(1, userName);
                ResultSet userResult = userStmt.executeQuery();
                if (userResult.next()) {
                    userId = userResult.getInt("user_id");
                } else {
                    JOptionPane.showMessageDialog(this, "User not found.");
                    return;
                }
            }

            String equipmentIdInput = JOptionPane.showInputDialog("Enter the equipment ID to rent:");
            int equipmentId = Integer.parseInt(equipmentIdInput);

            String rentalQuery = "INSERT INTO EquipmentRentals (user_id, equipment_id, rental_date) VALUES (?, ?, CURRENT_DATE)";
            try (PreparedStatement rentalStmt = connection.prepareStatement(rentalQuery)) {
                rentalStmt.setInt(1, userId);
                rentalStmt.setInt(2, equipmentId);

                rentalStmt.executeUpdate();

                String updateEquipmentQuery = "UPDATE Equipment SET available_quantity = available_quantity - 1 WHERE equipment_id = ?";
                try (PreparedStatement updateStmt = connection.prepareStatement(updateEquipmentQuery)) {
                    updateStmt.setInt(1, equipmentId);
                    updateStmt.executeUpdate();
                }

                JOptionPane.showMessageDialog(this, "Equipment rented successfully!");
            }

        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Invalid equipment ID. Please try again.");
        }
    }



}
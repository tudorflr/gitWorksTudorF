import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PostgreSQLData {

    // Method to fetch users from the database
    public static void fetchData(Connection conn) {
        String query = "SELECT * FROM Users";

        try (PreparedStatement stmt = conn.prepareStatement(query);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                int userId = rs.getInt("user_id");
                String username = rs.getString("username");
                String email = rs.getString("email");
                String fullName = rs.getString("full_name");
                String phoneNumber = rs.getString("phone_number");

                System.out.println("User ID: " + userId + ", Username: " + username + ", Email: " + email +
                        ", Full Name: " + fullName + ", Phone Number: " + phoneNumber);
            }

        } catch (SQLException e) {
            System.out.println("Query failed: " + e.getMessage());
        }
    }

    // Method to add a new user
    public static void addUser(Connection conn, String username, String email, String password,
                               String fullName, String phoneNumber) {
        String query = "INSERT INTO Users (username, email, password, full_name, phone_number) VALUES (?, ?, ?, ?, ?)";

        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setString(2, email);
            stmt.setString(3, password);
            stmt.setString(4, fullName);
            stmt.setString(5, phoneNumber);

            int rowsAffected = stmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("New user added successfully!");
            } else {
                System.out.println("Failed to add user.");
            }

        } catch (SQLException e) {
            System.out.println("Error adding user: " + e.getMessage());
        }
    }

    // Method to fetch appointments
    public static void fetchAppointments(Connection conn) {
        String query = "SELECT * FROM Appointments";

        try (PreparedStatement stmt = conn.prepareStatement(query);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                int appointmentId = rs.getInt("appointment_id");
                int userId = rs.getInt("user_id");
                int courtId = rs.getInt("court_id");
                int coachId = rs.getInt("coach_id");
                String status = rs.getString("status");

                System.out.println("Appointment ID: " + appointmentId + ", User ID: " + userId +
                        ", Court ID: " + courtId + ", Coach ID: " + coachId + ", Status: " + status);
            }

        } catch (SQLException e) {
            System.out.println("Query failed: " + e.getMessage());
        }
    }
}

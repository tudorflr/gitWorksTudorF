import java.sql.Connection;
import java.sql.SQLException;
import java.util.Scanner;

public class UserInterface {

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        try {
            Connection connection = DatabaseConnection.getConnection();

            showMenu();

            boolean running = true;
            while (running) {
                System.out.print("Please choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine();  // Consume the newline character

                switch (choice) {
                    case 1:
                        PostgreSQLData.fetchData(connection);
                        break;
                    case 2:
                        addUser(connection);
                        break;
                    case 3:
                        fetchAppointments(connection);
                        break;
                    case 4:
                        running = false;
                        break;
                    default:
                        System.out.println("Invalid option! Please try again.");
                }
            }

            connection.close();

        } catch (SQLException e) {
            System.out.println("Database connection failed: " + e.getMessage());
        }
    }

    private static void showMenu() {
        System.out.println("Welcome to the Tennis Database System!");
        System.out.println("1. Fetch all users");
        System.out.println("2. Add a new user");
        System.out.println("3. Fetch all appointments");
        System.out.println("4. Exit");
    }

    private static void addUser(Connection connection) {
        System.out.println("Enter user details:");
        System.out.print("Username: ");
        String username = scanner.nextLine();
        System.out.print("Email: ");
        String email = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();
        System.out.print("Full Name: ");
        String fullName = scanner.nextLine();
        System.out.print("Phone Number: ");
        String phoneNumber = scanner.nextLine();

        PostgreSQLData.addUser(connection, username, email, password, fullName, phoneNumber);
    }

    private static void fetchAppointments(Connection connection) {
        PostgreSQLData.fetchAppointments(connection);
    }
}

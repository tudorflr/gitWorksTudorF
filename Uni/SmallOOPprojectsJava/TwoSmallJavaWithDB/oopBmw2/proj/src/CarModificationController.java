import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.util.List;
import java.util.ArrayList;

public class CarModificationController {
    private final CarModificationView view;
    private final Connection connection;
    private RaceView viewRace;
    private static int initialHP, quarterFinal;
    private static String userName;

    public CarModificationController(CarModificationView view, Connection connection) {
        this.view = view;
        this.connection = connection;
        view.setButtonActionListener(new CalculatorListener());
        initialize();
    }

    private void initialize() {
        List<String> carModels = loadCarModels();
        List<String> exhaustMods = loadModifications("Exhaust");
        List<String> turboMods = loadModifications("Turbo");
        List<String> intakeMods = loadModifications("Intake");

        view.setCarModels(carModels);
        view.setModifications(exhaustMods, turboMods, intakeMods);
    }

    private List<String> loadCarModels() {
        List<String> carModels = new ArrayList<>();
        try {
            String query = "SELECT model_name FROM bmw_models";
            try (PreparedStatement stmt = connection.prepareStatement(query);
                 ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    carModels.add(rs.getString("model_name"));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            view.showMessage("Error loading car models: " + e.getMessage());
        }
        return carModels;
    }

    private List<String> loadModifications(String type) {
        List<String> modifications = new ArrayList<>();
        try {
            String query = "SELECT modification_id, modification_name FROM modifications WHERE type = ?";
            try (PreparedStatement stmt = connection.prepareStatement(query)) {
                stmt.setString(1, type);
                try (ResultSet rs = stmt.executeQuery()) {
                    while (rs.next()) {
                        modifications.add(rs.getInt("modification_id") + ": " + rs.getString("modification_name"));
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            view.showMessage("Error loading modifications: " + e.getMessage());
        }
        return modifications;
    }

    private int exportHpinfo(String partName) {
        int hp = 0;
        try {
            String[] parts = partName.split(":");
            if (parts.length > 1) {
                String modificationName = parts[1].trim();
                String query = "SELECT hp_increase FROM modifications WHERE modification_name = ?";
                try (PreparedStatement stmt = connection.prepareStatement(query)) {
                    stmt.setString(1, modificationName);
                    try (ResultSet rs = stmt.executeQuery()) {
                        if (rs.next()) {
                            hp = rs.getInt("hp_increase");
                        }
                    }
                }
            } else {
                view.showMessage("Invalid part name format.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            view.showMessage("Error fetching horsepower for modification: " + e.getMessage());
        }
        return hp;
    }

    private int exportModelHp(String modelName) {
        int hp = 0;
        try {
            String query = "SELECT horsepower FROM bmw_models WHERE model_name = ?";
            try (PreparedStatement stmt = connection.prepareStatement(query)) {
                stmt.setString(1, modelName);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        hp = rs.getInt("horsepower");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            view.showMessage("Error fetching horsepower for model: " + e.getMessage());
        }
        return hp;
    }

    public boolean exportCarBuild(String buildName, int horsepower, float quartermile) {
        String query = "INSERT INTO car_buildsfinal (build_name, horsepower, quartermile) VALUES (?, ?, ?)";

        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, buildName);
            stmt.setInt(2, horsepower);
            stmt.setFloat(3, quartermile);

            int rowsAffected = stmt.executeUpdate();
            return rowsAffected > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private class CalculatorListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String modelName = view.getJComboModel();
            String turbo = view.getJComboTurboType();
            String exhaust = view.getJComboExhaustType();
            String intake = view.getJComboIntakeType();

            int modelHP = exportModelHp(modelName);
            int turboVal = exportHpinfo(turbo);
            int exhaustVal = exportHpinfo(exhaust);
            int intakeVal = exportHpinfo(intake);

            CarModification carMod = new CarModification(0, "0", 0, 0, 0);
            int resultQuarter = carMod.HPCalculation(modelHP, turboVal, exhaustVal, intakeVal);

            initialHP = modelHP;
            quarterFinal = resultQuarter;

            viewRace = new RaceView();
            viewRace.setCatFace(String.valueOf(resultQuarter));

            try {
                Thread.sleep(10000);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }


            viewRace.setVisible(true);
            viewRace.setButtonActionListenerFinal(new CalculatorListenerRace());
        }
    }

    private class CalculatorListenerRace implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            userName = viewRace.numeTrimis();
            if (userName == null || userName.trim().isEmpty()) {
                viewRace.showMessage("Please enter a name before exporting.");
                return;
            }

            boolean exportSuccess = exportCarBuild(userName, quarterFinal, initialHP);
            if (exportSuccess) {
                viewRace.showMessage("Car build successfully exported!");
            } else {
                viewRace.showMessage("Error exporting car build.");
            }
        }
    }
}

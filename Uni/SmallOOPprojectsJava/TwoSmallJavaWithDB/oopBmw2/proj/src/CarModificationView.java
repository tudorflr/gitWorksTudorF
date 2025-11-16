import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.List;

public class CarModificationView extends JFrame {
    private JComboBox<String> carModelComboBox;
    private JComboBox<String> exhaustTypeComboBox;
    private JComboBox<String> turboTypeComboBox;
    private JComboBox<String> intakeTypeComboBox;
    private JButton exportBuildButton;
    private CarModificationController controller;

    public CarModificationView(CarModificationController controller) {
        this.controller = controller;

        setTitle("Car Modification");
        setLayout(new FlowLayout());
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        carModelComboBox = new JComboBox<>();
        carModelComboBox.setSelectedItem(null);

        exhaustTypeComboBox = new JComboBox<>();
        turboTypeComboBox = new JComboBox<>();
        intakeTypeComboBox = new JComboBox<>();

        exportBuildButton = new JButton("Da-i in gura vere");

        // Add components to frame
        add(new JLabel("Select Car Model:"));
        add(carModelComboBox);
        add(new JLabel("Select Exhaust Type:"));
        add(exhaustTypeComboBox);
        add(new JLabel("Select Turbo Type:"));
        add(turboTypeComboBox);
        add(new JLabel("Select Intake Type:"));
        add(intakeTypeComboBox);
        add(exportBuildButton);
    }

    public void setCarModels(List<String> carModels) {
        for (String model : carModels) {
            carModelComboBox.addItem(model);
        }
    }

    public void setModifications(List<String> exhaustMods, List<String> turboMods, List<String> intakeMods) {
        for (String mod : exhaustMods) {
            exhaustTypeComboBox.addItem(mod);
        }
        for (String mod : turboMods) {
            turboTypeComboBox.addItem(mod);
        }
        for (String mod : intakeMods) {
            intakeTypeComboBox.addItem(mod);
        }
    }

    // Get selected car and modifications
    public CarModification getSelectedCarModification() {
        String selectedCar = (String) carModelComboBox.getSelectedItem();
        String selectedExhaust = (String) exhaustTypeComboBox.getSelectedItem();
        String selectedTurbo = (String) turboTypeComboBox.getSelectedItem();
        String selectedIntake = (String) intakeTypeComboBox.getSelectedItem();
        return new CarModification(0, selectedCar,
                selectedTurbo != null ? Integer.parseInt(selectedTurbo.split(":")[0]) : -1,
                selectedExhaust != null ? Integer.parseInt(selectedExhaust.split(":")[0]) : -1,
                selectedIntake != null ? Integer.parseInt(selectedIntake.split(":")[0]) : -1);
    }

    // Show a message to the user
    public void showMessage(String message) {
        JOptionPane.showMessageDialog(this, message);
    }

    public String getJComboModel(){
        return carModelComboBox.getSelectedItem().toString();
    }

    public String getJComboExhaustType(){
        return exhaustTypeComboBox.getSelectedItem().toString();
    }

    public String getJComboTurboType(){
        return turboTypeComboBox.getSelectedItem().toString();
    }

    public String getJComboIntakeType(){
        return intakeTypeComboBox.getSelectedItem().toString();
    }

    public void setButtonActionListener(ActionListener actionListener) {
        exportBuildButton.addActionListener(actionListener);
    }

}

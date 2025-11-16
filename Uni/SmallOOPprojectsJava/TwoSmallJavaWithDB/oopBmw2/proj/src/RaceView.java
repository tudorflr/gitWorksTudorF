import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class RaceView extends JFrame {
    private final JLabel cursa;
    private final JTextField catFace;
    private final JTextField nume;
    private final JButton export;

    public RaceView() {
        cursa = new JLabel("atatia caluti face");
        catFace = new JTextField("");
        nume = new JTextField();
        export = new JButton("Export");

        setTitle("Race View");
        setLayout(new GridLayout(2, 2));
        setSize(350, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        add(cursa);
        add(catFace);
        add(nume);
        add(export);
    }

    public void setCatFace(String catFace) {
        this.catFace.setText(catFace);
    }

    public void setButtonActionListenerFinal(ActionListener actionListener) {
        export.addActionListener(actionListener);
    }

    public String numeTrimis() {
        return nume.getText();
    }

    public void showMessage(String message) {
        JOptionPane.showMessageDialog(this, message);
    }
}

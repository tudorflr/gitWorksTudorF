package presentation;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class MenuView extends JFrame {
    private final JButton clientButton = new JButton("Client Management");
    private final JButton productButton = new JButton("Product Management");
    private final JButton orderButton = new JButton("Order Management");

    public MenuView() {
        setTitle("Main Menu");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 150);
        setLayout(new GridLayout(3, 1, 10, 10));

        add(clientButton);
        add(productButton);
        add(orderButton);

        setLocationRelativeTo(null);
        setVisible(true);
    }

    // Provide methods for controller to add listeners:
    public void addClientButtonListener(ActionListener listener) {
        clientButton.addActionListener(listener);
    }

    public void addProductButtonListener(ActionListener listener) {
        productButton.addActionListener(listener);
    }

    public void addOrderButtonListener(ActionListener listener) { orderButton.addActionListener(listener); }

}
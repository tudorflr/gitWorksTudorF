package org.example.GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class WelcomeView extends JFrame {

    private final JLabel welcome;
    private final JButton proceed;

    public WelcomeView() {
        welcome = new JLabel("Welcome to Emoloyee manager", SwingConstants.CENTER);
        proceed = new JButton("Proceed");

        setTitle("EmployeeTask");
        setLayout(new GridLayout(2,1));
        setSize(230, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLocationRelativeTo(null);

        add(welcome);
        add(proceed);

        setVisible(true);
    }

    public void setButtonActionListener(ActionListener actionListener) {
        proceed.addActionListener(actionListener);
    }

}

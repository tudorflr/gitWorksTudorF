package org.example.GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class ResultView extends JFrame {

    private final JTextArea resultText;
    private final JButton returnButton;

    public ResultView() {
        setTitle("Result");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new BorderLayout());

        resultText = new JTextArea();
        resultText.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(resultText);

        returnButton = new JButton("Return");
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(returnButton);

        panel.add(scrollPane, BorderLayout.CENTER);
        panel.add(buttonPanel, BorderLayout.SOUTH);

        add(panel);

        //pack();
    }

    public void setResult(String result) {
        resultText.setText(result);
    }

    public void setButtonActionListenerReturn(ActionListener actionListener) {
        returnButton.addActionListener(actionListener);
    }
}

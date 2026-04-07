package cacheSimEngine;

import javax.swing.*;
import java.awt.*;

public class GuiMenuView extends JFrame {

    private final GuiMenuController controller;

    private final JTextField cacheSizeField = new JTextField(8);
    private final JTextField blockSizeField = new JTextField(8);
    private final JTextField waysField      = new JTextField(4);
    private final JComboBox<String> replacementBox =
            new JComboBox<>(new String[]{"FIFO", "RANDOM", "LRU"});
    private final JComboBox<String> writePolicyBox =
            new JComboBox<>(new String[]{
                    "Write-through (no-write-allocate)",
                    "Write-back (write-allocate)"
            });

    private final JTextArea traceArea  = new JTextArea(8, 40);
    private final JTextArea outputArea = new JTextArea(10, 40);

    private final JTextField traceFileField = new JTextField(20);
    private final JButton loadTraceButton   = new JButton("Load from file");

    JButton btnResetMem = new JButton("Reset memory");

    public GuiMenuView(GuiMenuController controller) {
        super("Cache Simulator");
        this.controller = controller;

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setResizable(false);

        add(createTopConfigPanel(), BorderLayout.NORTH);
        add(createCenterPanel(), BorderLayout.CENTER);
        add(createBottomButtons(), BorderLayout.SOUTH);

        pack();
        setLocationRelativeTo(null);
    }

    private JPanel createTopConfigPanel() {
        JPanel p = new JPanel(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.insets = new Insets(3,3,3,3);
        c.fill = GridBagConstraints.HORIZONTAL;

        //SimConfig cfg = controller.getConfig();
        SimConfig cfg = controller.getConfig();
        cacheSizeField.setText(String.valueOf(cfg.getCacheBytes()));
        blockSizeField.setText(String.valueOf(cfg.getBlockBytes()));
        waysField.setText(String.valueOf(cfg.getWays()));
        replacementBox.setSelectedIndex(cfg.getReplacementPolicy());
        writePolicyBox.setSelectedIndex(cfg.getWritePolicy());

        cacheSizeField.setText(String.valueOf(cfg.getCacheBytes()));
        blockSizeField.setText(String.valueOf(cfg.getBlockBytes()));
        waysField.setText(String.valueOf(cfg.getWays()));
        replacementBox.setSelectedIndex(cfg.getReplacementPolicy());

        int row = 0;

        c.gridx = 0; c.gridy = row; p.add(new JLabel("Cache size (bytes):"), c);
        c.gridx = 1; p.add(cacheSizeField, c);

        row++;
        c.gridx = 0; c.gridy = row; p.add(new JLabel("Block size (bytes):"), c);
        c.gridx = 1; p.add(blockSizeField, c);

        row++;
        c.gridx = 0; c.gridy = row; p.add(new JLabel("Ways:"), c);
        c.gridx = 1; p.add(waysField, c);

        row++;
        c.gridx = 0; c.gridy = row; p.add(new JLabel("Replacement:"), c);
        c.gridx = 1; p.add(replacementBox, c);

        row++;
        c.gridx = 0; c.gridy = row; p.add(new JLabel("Write policy:"), c);
        c.gridx = 1; p.add(writePolicyBox, c);

        return p;
    }

    private JPanel createCenterPanel() {
        JPanel p = new JPanel(new GridLayout(2, 1));

        traceArea.setBorder(BorderFactory.createTitledBorder(
                "Input trace (hex or decimal, space/newline separated)"
        ));
        outputArea.setBorder(BorderFactory.createTitledBorder("Output"));
        outputArea.setEditable(false);

        p.add(new JScrollPane(traceArea));
        p.add(new JScrollPane(outputArea));

        return p;
    }

    private JPanel createBottomButtons() {
        JPanel root = new JPanel(new BorderLayout());

        JPanel filePanel = new JPanel();
        filePanel.add(new JLabel("Trace file:"));
        traceFileField.setColumns(20);
        filePanel.add(traceFileField);
        filePanel.add(loadTraceButton);

        JPanel buttonsPanel = new JPanel();

        JButton btnStart  = new JButton("Start simulation");
        JButton btnStats  = new JButton("Show long-term statistics");
        JButton btnApply  = new JButton("Apply config / trace");

        btnResetMem.addActionListener(e -> {
            controller.resetMemory();
            outputArea.append("Main memory reset to initial state.\n");
        });

        btnApply.addActionListener(e -> applyConfigAndTrace());
        btnStart.addActionListener(e -> runSimulation());
        btnStats.addActionListener(e -> showStatisticsDialog());
        loadTraceButton.addActionListener(e -> loadTraceFromFile());

        buttonsPanel.add(btnApply);
        buttonsPanel.add(btnStart);
        buttonsPanel.add(btnStats);
        buttonsPanel.add(btnResetMem);

        root.add(filePanel, BorderLayout.NORTH);
        root.add(buttonsPanel, BorderLayout.SOUTH);

        return root;
    }

//    private void applyConfigAndTrace() {
//        try {
//            int cacheBytes = Integer.parseInt(cacheSizeField.getText().trim());
//            int blockBytes = Integer.parseInt(blockSizeField.getText().trim());
//            int ways       = Integer.parseInt(waysField.getText().trim());
//            int replIdx    = replacementBox.getSelectedIndex();
//
//            SimConfig cfg = controller.getConfig();
//            cfg.setCacheBytes(cacheBytes);
//            cfg.setBlockBytes(blockBytes);
//            cfg.setWays(ways);
//            cfg.changeReplacement(replIdx);
//
//            controller.setTraceFromText(traceArea.getText());
//
//            outputArea.append("Configuration and trace applied.\n");
//        } catch (NumberFormatException ex) {
//            JOptionPane.showMessageDialog(this,
//                    "Invalid number in configuration fields.",
//                    "Error", JOptionPane.ERROR_MESSAGE);
//        }
//    }

    private void applyConfigAndTrace() {
        try {
            int cacheBytes = Integer.parseInt(cacheSizeField.getText().trim());
            int blockBytes = Integer.parseInt(blockSizeField.getText().trim());

            if (blockBytes <= 0) {
                JOptionPane.showMessageDialog(this,
                        "Block size must be > 0.",
                        "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            // auto compute ways if text box is empty when applying config
            String waysText = waysField.getText().trim();
            int ways;

            if (waysText.isEmpty()) {
                ways = cacheBytes / blockBytes;

                if (ways < 1) {
                    ways = 1;
                }

                waysField.setText(String.valueOf(ways));

                outputArea.append(
                        String.format("Ways field empty → assuming fully associative: ways = cacheBytes/blockBytes = %d\n", ways)
                );
            } else {
                ways = Integer.parseInt(waysText);
            }

            int replIdx = replacementBox.getSelectedIndex();

            SimConfig cfg = controller.getConfig();
            cfg.setCacheBytes(cacheBytes);
            cfg.setBlockBytes(blockBytes);
            cfg.setWays(ways);
            cfg.changeReplacement(replIdx);

            cfg.setWritePolicy(writePolicyBox.getSelectedIndex());

            controller.setTraceFromText(traceArea.getText());

            outputArea.append("Configuration and trace applied.\n");
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this,
                    "Invalid number in configuration fields.",
                    "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void runSimulation() {
        outputArea.append("=== New simulation ===\n");
        String text = controller.startSimulation();
        outputArea.append(text);
        outputArea.append("\n");
    }

    private void showStatisticsDialog() {
        String stats = controller.getStatistics().getStatisticsText();

        JTextArea textArea = new JTextArea(20, 50);
        textArea.setText(stats);
        textArea.setEditable(false);
        textArea.setCaretPosition(0);

        JScrollPane scrollPane = new JScrollPane(
                textArea,
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED
        );

        JOptionPane.showMessageDialog(
                this,
                scrollPane,
                "Long-term Statistics",
                JOptionPane.INFORMATION_MESSAGE
        );
    }

    private void loadTraceFromFile() {
        String path = traceFileField.getText().trim();
        if (path.isEmpty()) {
            JOptionPane.showMessageDialog(
                    this,
                    "Please enter a trace file path.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
            return;
        }

        try {
            String content = java.nio.file.Files.readString(
                    java.nio.file.Path.of(path)
            );

            controller.setTraceFromText(content);

            traceArea.setText(content);

            outputArea.append("Trace loaded from file: " + path + "\n");
        } catch (java.io.IOException ex) {
            JOptionPane.showMessageDialog(
                    this,
                    "Could not read file:\n" + ex.getMessage(),
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(
                    this,
                    "Invalid address format in file. Use hex (0x10) or decimal, space/newline separated.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
        }
    }
}
/**
 * handles the logic between the client view and the bll layer
 *
 * sets up listeners for add/edit/delete/view buttons
 *
 * when a button is clicked, it reads data from the form using reflection,
 * builds a Client object, and calls the right method in ClientBLL
 *
 * buildClientFromForm uses reflection to match text fields to model fields
 *
 * errors like bad input are shown in a popup
 */

package presentation;

import business_layer.ClientBLL;
import model.Client;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class ClientController {
    private final ClientView view;
    private final ClientBLL clientBLL;

    public ClientController(ClientView view, ClientBLL clientBLL) {
        this.view = view;
        this.clientBLL = clientBLL;

        view.addAddListener(new AddListener());
        view.addEditListener(new EditListener());
        view.addDeleteListener(new DeleteListener());
        view.addViewAllListener(new ViewAllListener());
    }

    private Client buildClientFromForm() {
        try {
            Constructor<?> constructor = Client.class.getDeclaredConstructor();
            constructor.setAccessible(true);
            Client client = (Client) constructor.newInstance();

            Map<String, JTextField> fields = view.getFieldMap();
            for (Field field : Client.class.getDeclaredFields()) {
                field.setAccessible(true);
                String fieldName = field.getName();
                String value = view.getFieldValue(fieldName);
                if (value == null || value.isBlank()) continue;

                Class<?> type = field.getType();
                if (type == int.class || type == Integer.class) {
                    field.set(client, Integer.parseInt(value));
                } else {
                    field.set(client, value);
                }
            }

            return client;
        } catch (Exception e) {
            JOptionPane.showMessageDialog(view, "Invalid input: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            return null;
        }
    }

    // Listener classes
    private class AddListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            Client client = buildClientFromForm();
            if (client != null) {
                clientBLL.insertClient(client);
                JOptionPane.showMessageDialog(view, "Client added.");
            }
        }
    }

    private class EditListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            Client client = buildClientFromForm();
            if (client != null) {
                clientBLL.updateClient(client);
                JOptionPane.showMessageDialog(view, "Client updated.");
            }
        }
    }

    private class DeleteListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                String idText = view.getFieldValue("id");
                if (idText == null || idText.isBlank()) {
                    JOptionPane.showMessageDialog(view, "Please enter an ID to delete.");
                    return;
                }
                int id = Integer.parseInt(idText);
                clientBLL.deleteClient(id);
                JOptionPane.showMessageDialog(view, "Client deleted.");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(view, "Invalid ID format.");
            }
        }
    }

    private class ViewAllListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Client> clients = clientBLL.findAllClients();
            if (clients == null) clients = new ArrayList<>();
            view.displayClients(clients);
        }
    }
}
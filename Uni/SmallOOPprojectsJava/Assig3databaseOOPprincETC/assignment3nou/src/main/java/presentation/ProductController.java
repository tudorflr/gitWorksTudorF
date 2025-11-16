package presentation;

import business_layer.ProductBLL;
import model.Product;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * controls the interaction between the product view and the product business logic layer.
 * sets up action listeners for adding, editing, deleting, and viewing products.
 * builds product objects from the form fields using reflection.
 * shows messages to the user on operation success or error.
 */

public class ProductController {
    private final ProductView view;
    private final ProductBLL productBLL;

    public ProductController(ProductView view, ProductBLL productBLL) {
        this.view = view;
        this.productBLL = productBLL;

        view.addAddListener(new AddListener());
        view.addEditListener(new EditListener());
        view.addDeleteListener(new DeleteListener());
        view.addViewAllListener(new ViewAllListener());
    }

    // Utility: build Product from form fields
    private Product buildProductFromForm() {
        try {
            Constructor<?> constructor = Product.class.getDeclaredConstructor();
            constructor.setAccessible(true);
            Product product = (Product) constructor.newInstance();

            Map<String, JTextField> fields = view.getFieldMap();
            for (Field field : Product.class.getDeclaredFields()) {
                field.setAccessible(true);
                String fieldName = field.getName();
                String value = view.getFieldValue(fieldName);
                if (value == null || value.isBlank()) continue;

                Class<?> type = field.getType();
                if (type == int.class || type == Integer.class) {
                    field.set(product, Integer.parseInt(value));
                } else if (type == double.class || type == Double.class) {
                    field.set(product, Double.parseDouble(value));
                } else {
                    field.set(product, value);
                }
            }

            return product;
        } catch (Exception e) {
            JOptionPane.showMessageDialog(view, "Invalid input: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            return null;
        }
    }

    // Listener classes
    private class AddListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            Product product = buildProductFromForm();
            if (product != null) {
                productBLL.insertProduct(product);
                JOptionPane.showMessageDialog(view, "Product added.");
            }
        }
    }

    private class EditListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            Product product = buildProductFromForm();
            if (product != null) {
                productBLL.updateProduct(product);
                JOptionPane.showMessageDialog(view, "Product updated.");
            }
        }
    }

    private class DeleteListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                String idText = view.getFieldValue("id"); // Make sure your field is named "id"
                if (idText == null || idText.isBlank()) {
                    JOptionPane.showMessageDialog(view, "Please enter a Product ID to delete.");
                    return;
                }
                int id = Integer.parseInt(idText);
                productBLL.deleteProduct(id);
                JOptionPane.showMessageDialog(view, "Product deleted.");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(view, "Invalid Product ID format.");
            }
        }
    }

    private class ViewAllListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Product> products = productBLL.findAllProducts();
            if (products == null) products = new ArrayList<>();
            view.displayProducts(products);
        }
    }
}
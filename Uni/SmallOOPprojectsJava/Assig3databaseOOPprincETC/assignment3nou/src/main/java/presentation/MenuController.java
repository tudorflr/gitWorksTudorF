package presentation;

import business_layer.ClientBLL;
import business_layer.OrderBLL;
import business_layer.ProductBLL;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * starts and stops any needed Views
 */

public class MenuController {
    private final MenuView menuView;

    public MenuController(MenuView menuView) {
        this.menuView = menuView;

        this.menuView.addClientButtonListener(new ClientButtonListener());
        this.menuView.addProductButtonListener(new ProductButtonListener());
        this.menuView.addOrderButtonListener(new OrderButtonListener());
    }

    private class ClientButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            ClientView clientView = new ClientView();
            ClientBLL clientBLL = new ClientBLL();
            new ClientController(clientView, clientBLL);
            menuView.dispose(); // Close menu after opening client management
        }
    }

    private class ProductButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            ProductView productView = new ProductView();
            ProductBLL productBLL = new ProductBLL();
            new ProductController(productView, productBLL);
            menuView.dispose(); // Close menu after opening product management
        }
    }

    private class OrderButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            OrderView orderView = new OrderView();
            OrderBLL orderBLL = new OrderBLL();
            new OrderController(orderView, orderBLL);
            menuView.dispose(); // Close main menu
        }
    }

}
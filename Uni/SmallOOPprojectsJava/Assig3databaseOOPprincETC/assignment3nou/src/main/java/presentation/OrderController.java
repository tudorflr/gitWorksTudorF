package presentation;

import business_layer.OrderBLL;
import model.Orders;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

/**
 * handles the logic between the order view and the bll layer.
 * manages user interactions for adding, deleting, and viewing orders.
 * uses listeners to connect gui actions to business logic.
 */

public class OrderController {
    private final OrderView orderView;
    private final OrderBLL orderBLL;

    public OrderController(OrderView orderView, OrderBLL orderBLL) {
        this.orderView = orderView;
        this.orderBLL = orderBLL;

        this.orderView.addAddListener(new AddListener());
        this.orderView.addEditListener(new EditListener());
        this.orderView.addDeleteListener(new DeleteListener());
        this.orderView.addViewAllListener(new ViewAllListener());
    }

    class AddListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                int clientId = Integer.parseInt(orderView.getFieldValue("clientId"));
                int productId = Integer.parseInt(orderView.getFieldValue("productId"));
                int quantity = Integer.parseInt(orderView.getFieldValue("quantity"));

                Orders order = new Orders(clientId, productId, quantity);
                orderBLL.insertOrder(order);
                JOptionPane.showMessageDialog(orderView, "Order added successfully!");
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(orderView, "Error: " + ex.getMessage());
            }
        }
    }

    class EditListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JOptionPane.showMessageDialog(orderView, "Order editing not implemented.");
        }
    }

    class DeleteListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                int id = Integer.parseInt(orderView.getFieldValue("orderId"));
                orderBLL.deleteOrder(id);
                JOptionPane.showMessageDialog(orderView, "Order deleted successfully!");
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(orderView, "Error: " + ex.getMessage());
            }
        }
    }

    class ViewAllListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Orders> orders = orderBLL.findAllOrders();
            orderView.displayOrders(orders);
        }
    }
}
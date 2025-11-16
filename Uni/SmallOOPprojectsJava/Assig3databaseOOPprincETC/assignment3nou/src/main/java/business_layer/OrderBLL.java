package business_layer;

import data_access.OrderDAO;
import data_access.ProductDAO;
import model.Orders;
import model.Product;

import java.util.List;

/**
 * only BLL with something new implemented for finding products and clients by id
 *
 * others just implement the abstract functions
 **/

public class OrderBLL {

    private final OrderDAO orderDAO = new OrderDAO();
    private final ProductDAO productDAO = new ProductDAO();

    public void insertOrder(Orders orders) {
        Product product = productDAO.findById(orders.getProductId());
        if (product == null) {
            throw new IllegalArgumentException("Product not found with ID: " + orders.getProductId());
        }

        if (orders.getQuantity() > product.getStock()) {
            throw new IllegalArgumentException("Not enough stock for this product.");
        }

        // Update stock
        product.setStock(product.getStock() - orders.getQuantity());
        productDAO.update(product);

        orderDAO.insert(orders);
    }

    public void deleteOrder(int id) {
        orderDAO.delete(id);
    }

    public List<Orders> findAllOrders() {
        return orderDAO.findAll();
    }

    public void updateOrder(Orders orders) {
        // Not recommended unless you're re-adding validation & rollback
        orderDAO.update(orders);
    }


}
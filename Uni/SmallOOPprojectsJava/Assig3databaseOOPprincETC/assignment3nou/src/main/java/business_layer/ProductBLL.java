package business_layer;

import data_access.ProductDAO;
import model.Product;

import java.util.List;

public class ProductBLL {
    private final ProductDAO productDAO;

    public ProductBLL() {
        this.productDAO = new ProductDAO();
    }

    public void insertProduct(Product product) {
        productDAO.insert(product);
    }

    public void updateProduct(Product product) {
        productDAO.update(product);
    }

    public void deleteProduct(int id) {
        productDAO.delete(id);
    }

    public List<Product> findAllProducts() {
        return productDAO.findAll();
    }

    public Product findProductById(int id) {
        return productDAO.findById(id);
    }
}
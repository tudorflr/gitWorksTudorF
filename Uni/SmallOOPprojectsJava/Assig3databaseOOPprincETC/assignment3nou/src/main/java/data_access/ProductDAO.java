/**
 * all it does is extend the abstract class
 */

package data_access;

import model.Product;

public class ProductDAO extends AbstractDAO<Product> {

    public ProductDAO() {
        super(Product.class);
    }

}

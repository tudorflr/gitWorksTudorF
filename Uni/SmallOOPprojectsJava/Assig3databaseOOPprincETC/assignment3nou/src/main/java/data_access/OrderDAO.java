/**
 * all it does is extend the abstract class
 */

package data_access;

import model.Orders;

public class OrderDAO extends AbstractDAO<Orders> {

    public OrderDAO() {
        super(Orders.class);
    }

}

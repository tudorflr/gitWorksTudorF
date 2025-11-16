/**
 * all it does is extend the abstract class
 */

package data_access;

import model.Client;

public class ClientDAO extends AbstractDAO<Client> {

    public ClientDAO() {
        super(Client.class);
    }

}
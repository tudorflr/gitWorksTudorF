package business_layer;

import data_access.ClientDAO;
import model.Client;

import java.util.List;

public class ClientBLL {
    private final ClientDAO clientDAO;

    public ClientBLL() {
        this.clientDAO = new ClientDAO();
    }

    public void insertClient(Client client) {
        clientDAO.insert(client);
    }

    public void updateClient(Client client) {
        clientDAO.update(client);
    }

    public void deleteClient(int id) {
        clientDAO.delete(id);
    }

    public List<Client> findAllClients() {
        return clientDAO.findAll();
    }

    public Client findClientById(int id) {
        return clientDAO.findById(id);
    }
}
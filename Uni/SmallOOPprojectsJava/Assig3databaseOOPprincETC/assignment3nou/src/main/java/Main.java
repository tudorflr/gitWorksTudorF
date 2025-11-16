import presentation.MenuController;
import presentation.MenuView;

import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MenuView menuView = new MenuView();
            new MenuController(menuView);
        });
    }
}
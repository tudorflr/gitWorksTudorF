import cacheSimEngine.*;

public class Main {
    public static void main(String[] args) {
        int cacheBytes = 4 * 1024;
        int blockBytes = 16;
        int ways = 2;

        Memory mem = new Memory();
        SimConfig config = new SimConfig(cacheBytes, blockBytes, ways);
        Statistics stats = new Statistics();

        config.setInput(java.util.List.of(
                0x10L,
                0x1AL,
                0x1BL,
                0x1010L,
                0x1008L,
                0x0010L,
                0x1020L,
                0x1030L
        )); // 0x10 0x1A 0x1B 0x1010 0x1008 0x0010 0x1020 0x1030
            // 0x0010 0x1010 0x2010 0x3010 0x0010 0x1010 0x2010 0x3010 // misses all fifo x rand
            // 0x10 0x810 0x10 0x1010 0x810 0x10 // fifo x lru


        GuiMenuController controller = new GuiMenuController(config, stats, mem);

        javax.swing.SwingUtilities.invokeLater(() -> {
            GuiMenuView frame = new GuiMenuView(controller);
            frame.setVisible(true);
        });
    }
}

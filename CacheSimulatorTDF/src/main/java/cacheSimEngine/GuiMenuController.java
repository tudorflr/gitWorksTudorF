package cacheSimEngine;

import java.util.List;

public class GuiMenuController {

    private final SimConfig config;
    private final Statistics statistics;
    private final Memory memory;

    public GuiMenuController(SimConfig config, Statistics statistics, Memory memory) {
        this.config = config;
        this.statistics = statistics;
        this.memory = memory;
    }

    public void resetMemory() {
        memory.reset();
    }

    public SimConfig getConfig()      { return config; }
    public Statistics getStatistics() { return statistics; }

    public String startSimulation() {
        List<SimConfig.Access> trace = config.getAccessTrace();
        if (trace == null || trace.isEmpty()) {
            return "No input trace configured.\nUse 'Input trace' to set addresses first.\n";
        }

        CacheSimulator sim = config.createSimulator(memory);
        sim.startSimulation(trace);

        statistics.calculateAndStoreStat(
                String.format("cache=%dB, block=%dB, ways=%d, file=%s",
                        config.getCacheBytes(),
                        config.getBlockBytes(),
                        config.getWays(),
                        config.getInputFilePath()),
                sim.getAccesses(),
                sim.getHits(),
                sim.getMisses()
        );

        StringBuilder sb = new StringBuilder();
        for (String line : sim.getLogLines()) {
            sb.append(line).append("\n");
        }
        return sb.toString();
    }

    public void setTraceFromText(String text) {
        if (text == null || text.isBlank()) {
            config.setAccessTrace(List.of());
            return;
        }

        String[] tokens = text.split("\\s+");
        java.util.ArrayList<SimConfig.Access> list = new java.util.ArrayList<>();

        int i = 0;
        while (i < tokens.length) {
            String tok = tokens[i].trim();
            if (tok.isEmpty()) { i++; continue; }

            char c = Character.toUpperCase(tok.charAt(0));

            if ((c == 'R' || c == 'W') && tok.length() == 1) {
                if (i + 1 >= tokens.length) throw new NumberFormatException("Missing address after " + tok);
                long addr = parseNumber(tokens[++i]);

                if (c == 'R') {
                    list.add(new SimConfig.Access(false, addr, null));
                    i++;
                } else {
                    if (i + 1 >= tokens.length) throw new NumberFormatException("Missing value after W <addr>");
                    int val = (int) parseNumber(tokens[++i]);
                    if (val < 0 || val > 255) throw new NumberFormatException("Write value must be 0..255");
                    list.add(new SimConfig.Access(true, addr, val));
                    i++;
                }
            } else {
                long addr = parseNumber(tok);
                list.add(new SimConfig.Access(false, addr, null));
                i++;
            }
        }

        config.setAccessTrace(list);
    }

    private long parseNumber(String t) {
        t = t.trim();
        if (t.startsWith("0x") || t.startsWith("0X")) return Long.parseLong(t.substring(2), 16);
        return Long.parseLong(t);
    }


//    public void setTraceFromText(String text) {
//        if (text == null || text.isBlank()) {
//            config.setAccessTrace(List.of());
//            return;
//        }
//
//        String[] tokens = text.split("\\s+");
//        java.util.ArrayList<SimConfig.Access> list = new java.util.ArrayList<>();
//
//        int i = 0;
//        while (i < tokens.length) {
//            String tok = tokens[i].trim();
//            if (tok.isEmpty()) {
//                i++;
//                continue;
//            }
//
//            char c = Character.toUpperCase(tok.charAt(0));
//            if ((c == 'R' || c == 'W') && tok.length() == 1) {
//                // Explicit op, next token must be an address
//                if (i + 1 >= tokens.length) {
//                    throw new NumberFormatException("Missing address after " + tok);
//                }
//                String addrTok = tokens[++i].trim();
//                long addr = parseAddress(addrTok);
//                boolean isWrite = (c == 'W');
//                list.add(new SimConfig.Access(isWrite, addr));
//                i++;
//            } else {
//                // Bare address → default to READ
//                long addr = parseAddress(tok);
//                list.add(new SimConfig.Access(false, addr));
//                i++;
//            }
//        }
//
//        config.setAccessTrace(list);
//    }

    private long parseAddress(String t) {
        if (t.startsWith("0x") || t.startsWith("0X")) {
            return Long.parseLong(t.substring(2), 16);
        } else {
            return Long.parseLong(t);
        }
    }
}

//package cacheSimEngine;
//
//import java.util.List;
//
//public class GuiMenuController {
//
//    private final SimConfig config;
//    private final Statistics statistics;
//    private final Memory memory;
//
//    public GuiMenuController(SimConfig config, Statistics statistics, Memory memory) {
//        this.config = config;
//        this.statistics = statistics;
//        this.memory = memory;
//    }
//
//    public SimConfig getConfig()      { return config; }
//    public Statistics getStatistics() { return statistics; }
//
//    public String startSimulation() {
//        List<Long> trace = config.getAddressTrace();
//        if (trace == null || trace.isEmpty()) {
//            return "No input trace configured.\nUse 'Input trace' to set addresses first.\n";
//        }
//
//        CacheSimulator sim = config.createSimulator(memory);
//        sim.startSimulation(trace);
//
//        statistics.calculateAndStoreStat(
//                String.format("cache=%dB, block=%dB, ways=%d, file=%s",
//                        config.getCacheBytes(),
//                        config.getBlockBytes(),
//                        config.getWays(),
//                        config.getInputFilePath()),
//                sim.getAccesses(),
//                sim.getHits(),
//                sim.getMisses()
//        );
//
//        // string from logs
//        StringBuilder sb = new StringBuilder();
//        for (String line : sim.getLogLines()) {
//            sb.append(line).append("\n");
//        }
//        return sb.toString();
//    }
//
//    public void setTraceFromText(String text) {
//        if (text == null || text.isBlank()) {
//            config.setInput(List.of());
//            return;
//        }
//
//        String[] tokens = text.split("\\s+");
//        java.util.ArrayList<Long> list = new java.util.ArrayList<>();
//        for (String tok : tokens) {
//            if (tok.isBlank()) continue;
//            String t = tok.trim();
//            if (t.startsWith("0x") || t.startsWith("0X")) {
//                list.add(Long.parseLong(t.substring(2), 16));
//            } else {
//                list.add(Long.parseLong(t));
//            }
//        }
//        config.setInput(list);
//    }
//}
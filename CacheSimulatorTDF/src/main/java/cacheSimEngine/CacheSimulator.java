package cacheSimEngine;

import java.util.ArrayList;
import java.util.List;

public class CacheSimulator {

    private final ReplacementAndMap RandM;
    private final Set[] sets;
    private final Memory memory;

    private long hits = 0;
    private long misses = 0;
    private long accesses = 0;

    private final int replacementPolicy;
    private final int writePolicy;

    private static int u8(byte b) { return b & 0xFF; }

    private final List<String> logLines = new ArrayList<>();

    public CacheSimulator(int cacheBytes,
                          int blockBytes,
                          int ways,
                          Memory memory,
                          int replacementPolicy,
                          int writePolicy) {

        this.memory = memory;
        this.RandM = new ReplacementAndMap(cacheBytes, blockBytes, ways);
        this.replacementPolicy = replacementPolicy;
        this.writePolicy = writePolicy;

        this.sets = new Set[RandM.setsCount()];
        for (int i = 0; i < sets.length; i++) {
            sets[i] = new Set(
                    RandM.ways(),
                    RandM.blockBytes(),
                    replacementPolicy,
                    RandM,
                    writePolicy,
                    i,
                    memory
            );
        }
    }

    private void log(String msg) {
        logLines.add(msg);
        System.out.println(msg);
    }

    private void clearLog() {
        logLines.clear();
    }

    public List<String> getLogLines() {
        return logLines;
    }

    public void startSimulation(List<SimConfig.Access> accessTrace) {
        clearLog();
        log("=== Starting Cache Simulation ===");
        log(String.format("Write policy: %s",
                writePolicy == SimConfig.WRITE_THROUGH_NO_ALLOCATE
                        ? "Write-through (no-write-allocate)"
                        : "Write-back (write-allocate)"));

        for (SimConfig.Access acc : accessTrace) {
            processAccess(acc);
        }
        printStatistics();
    }

    private void processAccess(SimConfig.Access acc) {
        boolean isWrite = acc.isWrite();
        long address    = acc.getAddress();

        accesses++;

        ReplacementAndMap.Mapping m = RandM.map(address);
        Set set = sets[m.setIndex()];

        int hitIdx = set.findHit(m.tag());

        if (!isWrite) {
            if (hitIdx >= 0) {
                hits++;

                if (set.replacement == 2) { // LRU
                    RandM.onAccess(set.linesArr, hitIdx);
                }

                int value = u8(set.linesArr[hitIdx].getData()[m.offset()]);

                log(String.format(
                        "R addr=0x%08X | set=%3d | tag=%4d | off=%2d | HIT  (line=%d) | val=0x%02X",
                        address, m.setIndex(), m.tag(), m.offset(), hitIdx, value
                ));
            } else {
                misses++;

                byte[] block = memory.read(m.blockBase(), RandM.blockBytes());
                int victim = set.replace(m.tag(), block);

                int value = u8(set.linesArr[victim].getData()[m.offset()]);

                log(String.format(
                        "R addr=0x%08X | set=%3d | tag=%4d | off=%2d | MISS -> line=%d | val=0x%02X",
                        address, m.setIndex(), m.tag(), m.offset(), victim, value
                ));
            }
            return;
        }


        Integer wvObj = acc.getWriteValue();
        if (wvObj == null) {
            throw new IllegalArgumentException("Write access must include a value: W <addr> <value>");
        }
        int writeVal = wvObj & 0xFF;

        // Write-through (no-write-allocate)
        if (writePolicy == SimConfig.WRITE_THROUGH_NO_ALLOCATE) {

            if (hitIdx >= 0) {
                hits++;

                if (set.replacement == 2) { // LRU
                    RandM.onAccess(set.linesArr, hitIdx);
                }

                // update cache byte
                set.linesArr[hitIdx].getData()[m.offset()] = (byte) writeVal;

                // update memory immediately
                memory.writeByte((int) address, (byte) writeVal);

                log(String.format(
                        "W addr=0x%08X | set=%3d | tag=%4d | off=%2d | HIT  | WT | val=0x%02X",
                        address, m.setIndex(), m.tag(), m.offset(), writeVal
                ));
            } else {
                misses++;

                // no-write-allocate not load in cachee only update memory
                memory.writeByte((int) address, (byte) writeVal);

                log(String.format(
                        "W addr=0x%08X | set=%3d | tag=%4d | off=%2d | MISS | WT(no-alloc) | val=0x%02X",
                        address, m.setIndex(), m.tag(), m.offset(), writeVal
                ));
            }
            return;
        }

        // Write-back (write-allocate)
        if (hitIdx >= 0) {
            hits++;

            if (set.replacement == 2) { // LRU
                RandM.onAccess(set.linesArr, hitIdx);
            }

            // update cache byte mark dirty
            set.linesArr[hitIdx].getData()[m.offset()] = (byte) writeVal;
            set.linesArr[hitIdx].setDirty(true);

            log(String.format(
                    "W addr=0x%08X | set=%3d | tag=%4d | off=%2d | HIT  | WB(dirty) | val=0x%02X",
                    address, m.setIndex(), m.tag(), m.offset(), writeVal
            ));
        } else {
            misses++;

            // write-allocate bring block into cache first
            byte[] block = memory.read(m.blockBase(), RandM.blockBytes());
            int victim = set.replace(m.tag(), block);

            // then update byte mark dirty
            set.linesArr[victim].getData()[m.offset()] = (byte) writeVal;
            set.linesArr[victim].setDirty(true);

            log(String.format(
                    "W addr=0x%08X | set=%3d | tag=%4d | off=%2d | MISS -> line=%d | WB(dirty) | val=0x%02X",
                    address, m.setIndex(), m.tag(), m.offset(), victim, writeVal
            ));
        }
    }


    private void printStatistics() {
        double hitRatio = accesses == 0 ? 0 : (double) hits / accesses * 100.0;
        double missRatio = 100.0 - hitRatio;

        log("");
        log("=== Simulation Summary ===");
        log(String.format("Accesses : %d", accesses));
        log(String.format("Hits     : %d", hits));
        log(String.format("Misses   : %d", misses));
        log(String.format("Hit Ratio: %.2f%%", hitRatio));
        log(String.format("Miss Ratio: %.2f%%", missRatio));
        log("============================");
    }

    public long getHits()     { return hits; }
    public long getMisses()   { return misses; }
    public long getAccesses() { return accesses; }
}

//package cacheSimEngine;
//
//import java.util.ArrayList;
//import java.util.List;
//
//public class CacheSimulator {
//
//    private final ReplacementAndMap RandM;
//    private final Set[] sets;
//    private final Memory memory;
//
//    private long hits = 0;
//    private long misses = 0;
//    private long accesses = 0;
//    private final int replacementPolicy;
//
//    private final List<String> logLines = new ArrayList<>();
//
//    public CacheSimulator(int cacheBytes, int blockBytes, int ways, Memory memory, int replacementPolicy) {
//        this.memory = memory;
//        this.RandM = new ReplacementAndMap(cacheBytes, blockBytes, ways);
//        this.replacementPolicy = replacementPolicy;
//
//        this.sets = new Set[RandM.setsCount()];
//        for (int i = 0; i < sets.length; i++) {
//            sets[i] = new Set(RandM.ways(), RandM.blockBytes(), replacementPolicy, RandM);
//        }
//    }
//
//    private void log(String msg) {
//        logLines.add(msg);
//        System.out.println(msg);
//    }
//
//    private void clearLog() {
//        logLines.clear();
//    }
//
//    public List<String> getLogLines() {
//        return logLines;
//    }
//
//    public void startSimulation(List<Long> addressTrace) {
//        clearLog();
//        log("=== Starting Cache Simulation ===");
//        for (long address : addressTrace) {
//            lookupAddress(address);
//        }
//        printStatistics();
//    }
//
//    public boolean lookupAddress(long address) {
//        accesses++;
//
//        ReplacementAndMap.Mapping m = RandM.map(address);
//        Set set = sets[m.setIndex()];
//
//        int hitIdx = set.findHit(m.tag());
//        if (hitIdx >= 0) {
//            hits++;
//
//            if (set.replacement == 2) { // 2 doar pt LRU
//                RandM.onAccess(set.linesArr, hitIdx);
//            }
//
//            //RandM.onAccess(set.linesArr, hitIdx);
//
//            String line = String.format(
//                    "addr=0x%08X | set=%3d | tag=%4d | HIT  (line=%d)",
//                    address, m.setIndex(), m.tag(), hitIdx
//            );
//            log(line);
//            return true;
//        } else {
//            misses++;
//            byte[] block = memory.read(m.blockBase(), RandM.blockBytes());
//            int victim = set.replace(m.tag(), block);
//            String line = String.format(
//                    "addr=0x%08X | set=%3d | tag=%4d | MISS -> replaced line=%d",
//                    address, m.setIndex(), m.tag(), victim
//            );
//            log(line);
//            return false;
//        }
//    }
//
//    private void printStatistics() {
//        double hitRatio = accesses == 0 ? 0 : (double) hits / accesses * 100.0;
//        double missRatio = 100.0 - hitRatio;
//
//        log("");
//        log("=== Simulation Summary ===");
//        log(String.format("Accesses : %d", accesses));
//        log(String.format("Hits     : %d", hits));
//        log(String.format("Misses   : %d", misses));
//        log(String.format("Hit Ratio: %.2f%%", hitRatio));
//        log(String.format("Miss Ratio: %.2f%%", missRatio));
//        log("============================");
//    }
//
//    public long getHits()     { return hits; }
//    public long getMisses()   { return misses; }
//    public long getAccesses() { return accesses; }
//}
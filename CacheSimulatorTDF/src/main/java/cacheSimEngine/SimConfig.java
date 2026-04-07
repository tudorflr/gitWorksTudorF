package cacheSimEngine;

import java.util.ArrayList;
import java.util.List;

public class SimConfig {

    public static class Access {
        private final boolean write;
        private final long address;
        private final Integer writeValue; // null for reads

        public Access(boolean write, long address, Integer writeValue) {
            this.write = write;
            this.address = address;
            this.writeValue = writeValue;
        }

        public boolean isWrite() { return write; }
        public long getAddress() { return address; }
        public Integer getWriteValue() { return writeValue; }
    }

    private int cacheBytes;
    private int blockBytes;
    private int ways;

    private int replacementPolicy = 0;

    private String mappingDescription = "set-associative";

    private String inputFilePath;

    private List<Long> addressTrace = new ArrayList<>();

    private final List<Access> accessTrace = new ArrayList<>();

    public static final int WRITE_THROUGH_NO_ALLOCATE = 0;
    public static final int WRITE_BACK_WRITE_ALLOCATE = 1;

    private int writePolicy = WRITE_THROUGH_NO_ALLOCATE; // default

    public SimConfig(int cacheBytes, int blockBytes, int ways) {
        this.cacheBytes = cacheBytes;
        this.blockBytes = blockBytes;
        this.ways = ways;
    }

    public void setInput(List<Long> trace) {
        this.addressTrace.clear();
        this.accessTrace.clear();
        if (trace != null) {
            this.addressTrace.addAll(trace);
            for (Long addr : trace) {
                if (addr != null) {
                    //this.accessTrace.add(new Access(false, addr));
                    this.accessTrace.add(new Access(false, addr, null));
                }
            }
        }
    }

    public void setAccessTrace(List<Access> trace) {
        this.addressTrace.clear();
        this.accessTrace.clear();
        if (trace != null) {
            this.accessTrace.addAll(trace);
        }
    }

    public List<Access> getAccessTrace() {
        return accessTrace;
    }

    public void selectFile(String path) {
        this.inputFilePath = path;
    }

    public void changeReplacement(int newPolicy) {
        if (newPolicy < 0 || newPolicy > 2) {
            System.out.println("Invalid replacement policy, keeping old value.");
            return;
        }
        this.replacementPolicy = newPolicy;
    }

    public void changeMapping(int newWays, int newBlockBytes) {
        if (newWays > 0) {
            this.ways = newWays;
        }
        if (newBlockBytes > 0) {
            this.blockBytes = newBlockBytes;
        }
    }

    public CacheSimulator createSimulator(Memory memory) {
        return new CacheSimulator(
                cacheBytes,
                blockBytes,
                ways,
                memory,
                replacementPolicy,
                writePolicy
        );
    }

    public List<Long> getAddressTrace() {
        return addressTrace;
    }

    public String getInputFilePath() {
        return inputFilePath;
    }

    public int getCacheBytes() {
        return cacheBytes;
    }

    public int getBlockBytes() {
        return blockBytes;
    }

    public int getWays() {
        return ways;
    }

    public int getReplacementPolicy() {
        return replacementPolicy;
    }

    public String getMappingDescription() {
        return mappingDescription;
    }

    public void setMappingDescription(String mappingDescription) {
        this.mappingDescription = mappingDescription;
    }

    public void setCacheBytes(int cacheBytes) {
        this.cacheBytes = cacheBytes;
    }

    public void setBlockBytes(int blockBytes) {
        this.blockBytes = blockBytes;
    }

    public void setWays(int ways) {
        this.ways = ways;
    }

    public int getWritePolicy() {
        return writePolicy;
    }

    public void setWritePolicy(int writePolicy) {
        this.writePolicy = writePolicy;
    }
}

//package cacheSimEngine;
//
//import java.util.ArrayList;
//import java.util.List;
//
//public class SimConfig {
//
//    private int cacheBytes;
//    private int blockBytes;
//    private int ways;
//
//
//    private int replacementPolicy = 0;
//
//    private String mappingDescription = "set-associative";
//
//    private String inputFilePath;
//    private List<Long> addressTrace = new ArrayList<>();
//
//    // Write policy constants
//    public static final int WRITE_THROUGH_NO_ALLOCATE = 0;
//    public static final int WRITE_BACK_WRITE_ALLOCATE = 1;
//
//    private int writePolicy = WRITE_THROUGH_NO_ALLOCATE; // default
//
//    public SimConfig(int cacheBytes, int blockBytes, int ways) {
//        this.cacheBytes = cacheBytes;
//        this.blockBytes = blockBytes;
//        this.ways = ways;
//    }
//
//    public void setInput(List<Long> trace) {
//        this.addressTrace.clear();
//        if (trace != null) {
//            this.addressTrace.addAll(trace);
//        }
//    }
//
//    public void selectFile(String path) {
//        this.inputFilePath = path;
//        // urmeaza input file
//    }
//
//    public void changeReplacement(int newPolicy) {
//        if (newPolicy < 0 || newPolicy > 2) {
//            System.out.println("Invalid replacement policy, keeping old value.");
//            return;
//        }
//        this.replacementPolicy = newPolicy;
//    }
//
//    public void changeMapping(int newWays, int newBlockBytes) {
//        if (newWays > 0) {
//            this.ways = newWays;
//        }
//        if (newBlockBytes > 0) {
//            this.blockBytes = newBlockBytes;
//        }
//    }
//
//    public CacheSimulator createSimulator(Memory memory) {
//        return new CacheSimulator(cacheBytes, blockBytes, ways, memory, replacementPolicy);
//    }
//
//    public List<Long> getAddressTrace() {
//        return addressTrace;
//    }
//
//    public String getInputFilePath() {
//        return inputFilePath;
//    }
//
//    public int getCacheBytes() {
//        return cacheBytes;
//    }
//
//    public int getBlockBytes() {
//        return blockBytes;
//    }
//
//    public int getWays() {
//        return ways;
//    }
//
//    public int getReplacementPolicy() {
//        return replacementPolicy;
//    }
//
//    public String getMappingDescription() {
//        return mappingDescription;
//    }
//
//    public void setMappingDescription(String mappingDescription) {
//        this.mappingDescription = mappingDescription;
//    }
//
//    public void setCacheBytes(int cacheBytes) {
//        this.cacheBytes = cacheBytes;
//    }
//
//    public void setBlockBytes(int blockBytes) {
//        this.blockBytes = blockBytes;
//    }
//
//    public void setWays(int ways) {
//        this.ways = ways;
//    }
//
//    public int getWritePolicy() {
//        return writePolicy;
//    }
//
//    public void setWritePolicy(int writePolicy) {
//        this.writePolicy = writePolicy;
//    }
//
//}
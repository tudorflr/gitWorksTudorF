package cacheSimEngine;

public class ReplacementAndMap {

    public record Mapping(int setIndex, long tag, int offset, long blockNumber, long blockBase) {}

    private int cacheBytes, blockBytes, ways, setsCount;

    private final java.util.Random random = new java.util.Random();

    private long tick = 0;
    private long nextTick() { return ++tick; }

    public ReplacementAndMap(int cacheBytes, int blockBytes, int ways) {
        configure(cacheBytes, blockBytes, ways);
    }

    public void configure(int cacheBytes, int blockBytes, int ways) {
        this.cacheBytes = cacheBytes;
        this.blockBytes = blockBytes;
        this.ways       = Math.max(1, ways);

        int totalLines = Math.max(1, cacheBytes / blockBytes);
        this.setsCount = Math.max(1, totalLines / this.ways);
    }

    public Mapping map(long address) {
        int  offset      = (int)(address % blockBytes);
        long blockNumber = address / blockBytes;
        int  set         = (int)(blockNumber % setsCount);
        long tag         = blockNumber / setsCount;
        long blockBase   = blockNumber * (long)blockBytes;
        return new Mapping(set, tag, offset, blockNumber, blockBase);
    }

    public int blockBytes(){ return blockBytes; }
    public int setsCount(){ return setsCount; }
    public int ways(){ return ways; }

//    public int applyReplacement(CacheLine[] linesArr) {
//        int victim = 0;
//        long oldest = Long.MAX_VALUE;
//        for (int i = 0; i < linesArr.length; i++) {
//            if (linesArr[i].meta < oldest) { oldest = linesArr[i].meta; victim = i; }
//        }
//        return victim;
//    }

    // FIFO choose the smallest meta
    public int fifoVictim(CacheLine[] linesArr) {
        int victim = 0;
        long oldest = Long.MAX_VALUE;
        for (int i = 0; i < linesArr.length; i++) {
            if (linesArr[i].meta < oldest) {
                oldest = linesArr[i].meta;
                victim = i;
            }
        }
        return victim;
    }

    // RANDOM
    public int randomVictim(int ways) {
        return random.nextInt(ways);
    }

    // LRU choose smallest meta, but meta is updated on access
    public int lruVictim(CacheLine[] linesArr) {
        return fifoVictim(linesArr);
    }

    public void onInsert(CacheLine[] linesArr, int idx) {
        linesArr[idx].meta = nextTick();
    }

   // public void onAccess(CacheLine[] linesArr, int idx) { /* no-op for FIFO */ }
    public void onAccess(CacheLine[] linesArr, int idx) {
        linesArr[idx].meta = nextTick();
    }
}
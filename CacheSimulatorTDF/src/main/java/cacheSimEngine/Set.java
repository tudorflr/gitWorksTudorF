package cacheSimEngine;

public class Set {

    public final CacheLine[] linesArr;
    public int replacement = 0; // 0 - FIFO, 1 - RANDOM, 2 - LRU
    public int ways = 0;
    public int blockBytes = 0;

    private final ReplacementAndMap RandM;
    private final int writePolicy;
    private final int setIndex;
    private final Memory memory;

    public Set(int ways,
               int blockBytes,
               int replacement,
               ReplacementAndMap randm,
               int writePolicy,
               int setIndex,
               Memory memory) {

        this.ways = ways;
        this.blockBytes = blockBytes;
        this.replacement = replacement;
        this.RandM = randm;
        this.writePolicy = writePolicy;
        this.setIndex = setIndex;
        this.memory = memory;

        linesArr = new CacheLine[ways];
        for (int i = 0; i < ways; i++) {
            linesArr[i] = new CacheLine(blockBytes);
        }
    }

    public int findHit(long tag){
        for(int i = 0; i < linesArr.length; i++){
            if (linesArr[i].matches(tag)){
                return i;
            }
        }
        return -1;
    }

    public int replace(long newTag, byte[] block){
        for (int i = 0; i < linesArr.length; i++){
            if (!linesArr[i].isValid()){
                fill(linesArr[i], newTag, block);
                RandM.onInsert(linesArr, i);
                return i;
            }
        }

        int victim;
        switch (replacement) {
            case 1: // RANDOM
                victim = RandM.randomVictim(linesArr.length);
                break;

            case 2: // LRU
                victim = RandM.lruVictim(linesArr);
                break;

            default: // FIFO
                victim = RandM.fifoVictim(linesArr);
        }

        CacheLine victimLine = linesArr[victim];

        // if write back policy and victim is dirty write back to memory
        if (writePolicy == SimConfig.WRITE_BACK_WRITE_ALLOCATE
                && victimLine.isValid()
                && victimLine.isDirty()) {

            long victimTag = victimLine.getTag();
            // blockNumber = tag * setsCount + setIndex
            long blockNumber = victimTag * RandM.setsCount() + setIndex;
            long blockBase   = blockNumber * (long) blockBytes;
            memory.writeBlock(blockBase, victimLine.getData());
            victimLine.setDirty(false);
        }

        // fill new data into victim line
        fill(victimLine, newTag, block);
        RandM.onInsert(linesArr, victim);
        return victim;
    }

    private void fill(CacheLine lineC, long tag, byte[] block) {
        lineC.setValid(true);
        lineC.setDirty(false);  // abia incarcat din mem
        lineC.setTag(tag);
        if (block != null && block.length == lineC.getDataLength())
            System.arraycopy(block, 0, lineC.getData(), 0, block.length);
    }
}

//package cacheSimEngine;
//
//public class Set {
//
//    public CacheLine[] linesArr;
//    public int replacement = 0; // 0 - fifo // 1 - random // 2 - LRU
//    public int ways = 0;
//    public int blockBytes = 0;
//    //ReplacementAndMap RandM = new ReplacemntAndMap(replacement, others as in map values? );
//    ReplacementAndMap RandM;
//
//    public Set(int ways, int blockBytes, int replacement, ReplacementAndMap randm){
//        this.ways = ways;
//        this.blockBytes = blockBytes;
//        this.replacement = replacement;
//        this.RandM = randm;
//        generateActualLines();
//    }
//
//    private void generateActualLines(){
//        linesArr = new CacheLine[ways];
//        for (int i = 0; i < ways; i++){
//            linesArr[i] = new CacheLine(blockBytes);
//        }
//    }
//
//    public int findHit(long tag){
//        for(int i = 0; i < linesArr.length; i++){
//            if (linesArr[i].matches(tag)){
//                return i;
//            }
//        }
//        return -1;
//    }
//
////    public int replace(long newTag, byte[] block){
////        for (int i = 0; i < linesArr.length; i++){
////            if (!linesArr[i].isValid()){
////                fill(linesArr[i], newTag, block);
////                RandM.onInsert(linesArr, i);
////                return i;
////            }
////        }
////        int victim = RandM.applyReplacement(linesArr);
////        fill(linesArr[victim], newTag, block);
////        RandM.onInsert(linesArr, victim);
////        return victim;
////    }
//
//    public int replace(long newTag, byte[] block){
//        // linie goala
//        for (int i = 0; i < linesArr.length; i++){
//            if (!linesArr[i].isValid()){
//                fill(linesArr[i], newTag, block);
//                RandM.onInsert(linesArr, i);
//                return i;
//            }
//        }
//
//        // victim by replac
//        int victim;
//        switch (replacement) {
//            case 1: // RANDOM
//                victim = RandM.randomVictim(linesArr.length);
//                break;
//
//            case 2: // LRU
//                victim = RandM.lruVictim(linesArr);
//                break;
//
//            default: // FIFO
//                victim = RandM.fifoVictim(linesArr);
//        }
//
//        fill(linesArr[victim], newTag, block);
//        RandM.onInsert(linesArr, victim);
//        return victim;
//    }
//
//    private void fill(CacheLine lineC, long tag, byte[] block) {
//        lineC.setValid(true);
//        lineC.setTag(tag);
//        if (block != null && block.length == lineC.getDataLength())
//            System.arraycopy(block, 0, lineC.getData(), 0, block.length);
//    }
//
//}

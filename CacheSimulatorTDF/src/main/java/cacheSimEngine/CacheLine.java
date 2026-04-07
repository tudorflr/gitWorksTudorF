package cacheSimEngine;

public class CacheLine {

    private boolean valid = false;
    private boolean dirty = false;
    private long tag = 0;
    private final byte[] data;
    public long meta = 0;

    public CacheLine(int blockBytes){
        this.data = new byte[blockBytes];
    }

    public boolean matches(long t){
        return valid && tag == t;
    }

    public boolean isValid() {
        return valid;
    }

    public boolean isDirty() {
        return dirty;
    }

    public long getTag() {
        return tag;
    }

    public byte[] getData() {
        return data;
    }

    public void setValid(boolean valid) {
        this.valid = valid;
    }

    public void setDirty(boolean dirty) {
        this.dirty = dirty;
    }

    public void setTag(long tag) {
        this.tag = tag;
    }

    public int getDataLength(){
        return data.length;
    }
}

//package cacheSimEngine;
//
//public class CacheLine {
//
//    private boolean valid = false;
//    private long tag = 0;
//    private final byte[] data;
//    public long meta = 0;
//
//    public CacheLine(int blockBytes){
//        this.data = new byte[blockBytes];
//    }
//
//    public boolean matches(long t){
//        return valid && tag == t;
//    }
//
//    public boolean isValid() {
//        return valid;
//    }
//
//    public long getTag() {
//        return tag;
//    }
//
//    public byte[] getData() {
//        return data;
//    }
//
//    public void setValid(boolean valid) {
//        this.valid = valid;
//    }
//
//    public void setTag(long tag) {
//        this.tag = tag;
//    }
//    public int getDataLength(){
//        return data.length;
//    }
//
//}

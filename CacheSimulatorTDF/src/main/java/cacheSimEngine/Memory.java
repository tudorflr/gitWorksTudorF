package cacheSimEngine;

public class Memory {

    public static final int SIZE_BYTES = 4 * 1024 * 1024;
    private final byte[] ram = new byte[SIZE_BYTES];

    public Memory() {
        reset();
    }

    public void reset() {
        for (int i = 0; i < ram.length; i++) {
            ram[i] = (byte) (i & 0xFF);
        }
    }

    public byte[] read(long blockBaseAddress, int blockBytes) {
        int addr = (int) blockBaseAddress;
        byte[] block = new byte[blockBytes];
        System.arraycopy(ram, addr, block, 0, blockBytes);
        return block;
    }

    public void writeByte(int addr, byte val) {
        ram[addr] = val;
    }

    public byte readByte(int addr) {
        return ram[addr];
    }

    public void writeBlock(long blockBaseAddress, byte[] data) {
        int addr = (int) blockBaseAddress;
        System.arraycopy(data, 0, ram, addr, data.length);
    }
}
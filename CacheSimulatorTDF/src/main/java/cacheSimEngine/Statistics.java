package cacheSimEngine;

import java.util.ArrayList;
import java.util.List;

public class Statistics {

    private static class Entry {
        final String label;
        final long accesses;
        final long hits;
        final long misses;
        final double hitRatio;
        final double missRatio;

        Entry(String label, long accesses, long hits, long misses) {
            this.label = label;
            this.accesses = accesses;
            this.hits = hits;
            this.misses = misses;
            this.hitRatio = accesses == 0 ? 0.0 : (hits * 100.0) / accesses;
            this.missRatio = 100.0 - this.hitRatio;
        }
    }

    private final List<Entry> history = new ArrayList<>();

    public void calculateAndStoreStat(String label,
                                      long accesses,
                                      long hits,
                                      long misses) {
        history.add(new Entry(label, accesses, hits, misses));
    }

    public String getStatisticsText() {
        if (history.isEmpty()) {
            return "No statistics recorded yet.\n";
        }

        int runs = history.size();
        long totalAccesses = 0;
        long totalHits = 0;
        long totalMisses = 0;
        double sumHitRatio = 0.0;

        Entry best = null;
        Entry worst = null;

        for (Entry e : history) {
            totalAccesses += e.accesses;
            totalHits += e.hits;
            totalMisses += e.misses;
            sumHitRatio += e.hitRatio;

            if (best == null || e.hitRatio > best.hitRatio) {
                best = e;
            }
            if (worst == null || e.hitRatio < worst.hitRatio) {
                worst = e;
            }
        }

        double globalHitRatio = totalAccesses == 0 ? 0.0 : (totalHits * 100.0) / totalAccesses;
        double globalMissRatio = 100.0 - globalHitRatio;
        double avgHitRatioPerRun = runs == 0 ? 0.0 : (sumHitRatio / runs);

        StringBuilder sb = new StringBuilder();

        sb.append("=== Long-Term Overview ===\n");
        sb.append("Simulations run        : ").append(runs).append("\n");
        sb.append("Total accesses         : ").append(totalAccesses).append("\n");
        sb.append("Total hits             : ").append(totalHits).append("\n");
        sb.append("Total misses           : ").append(totalMisses).append("\n");
        sb.append(String.format("Overall hit ratio      : %.2f%%%n", globalHitRatio));
        sb.append(String.format("Overall miss ratio     : %.2f%%%n", globalMissRatio));
        sb.append(String.format("Avg hit ratio / run    : %.2f%%%n", avgHitRatioPerRun));

        if (best != null) {
            sb.append(String.format("Best simulation        : %s (%.2f%% hit)%n",
                    best.label, best.hitRatio));
        }
        if (worst != null) {
            sb.append(String.format("Worst simulation       : %s (%.2f%% hit)%n",
                    worst.label, worst.hitRatio));
        }

        sb.append("\n");

        sb.append("=== Simulation History ===\n\n");

        int idx = 1;
        for (Entry e : history) {
            sb.append(idx++).append(") ").append(e.label).append("\n")
                    .append("   Accesses : ").append(e.accesses).append("\n")
                    .append("   Hits     : ").append(e.hits).append("\n")
                    .append("   Misses   : ").append(e.misses).append("\n")
                    .append(String.format("   Hit Ratio : %.2f%%%n", e.hitRatio))
                    .append(String.format("   Miss Ratio: %.2f%%%n", e.missRatio))
                    .append("\n");
        }

        sb.append("============================\n");
        return sb.toString();
    }
}
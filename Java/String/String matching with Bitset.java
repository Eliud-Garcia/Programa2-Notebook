
//String matching using a bitset


    static final int N =(int) 1e6+1;
    static BitSet[] mask = new BitSet[26];
    static String text;
    static String pattern;
    static BitSet startMask = new BitSet(N);
    
    static void computeMask(String text) {
        text = "#" + text; // to make text 1-indexed.
        for (int i = 0; i < 26; i++) {
            mask[i] = new BitSet(N);
        }
        for (int i = 1; i < text.length(); ++i) {
            int c = text.charAt(i) - 'a';
            mask[c].set(i);
        }
    }

    static int match(String pattern, String text) {
        if (pattern.length() > text.length()) {
            return 0;
        }
        pattern = "#" + pattern;
        startMask.set(0, N, true); // all bits are set to true
        for (int i = 1; i < pattern.length(); ++i) {
            int c = pattern.charAt(i) - 'a';
            startMask.and(mask[c].get(i, N));
        }
        return startMask.cardinality(); // cardinality() returns the number of true bits
    }
    

    static int rangePatternMatchCount(String pattern, int l, int r) {
        if (r - l + 1 < pattern.length()) {
            return 0;
        }
        pattern = "#" + pattern;
        startMask.set(0, N, true);
        for (int i = 1; i < pattern.length(); ++i) {
            int c = pattern.charAt(i) - 'a';
            startMask.and(mask[c].get(i, N));
        }
        return startMask.get(l - 1, r - pattern.length() + 2).cardinality();
    }

    static List<Integer> rangePatternPositions(String pattern, int l, int r) {
        int rangeCount = rangePatternMatchCount(pattern, l, r);
        List<Integer> positions = new ArrayList<>();
        for (int i = l - 1, idx = 0; i < r - pattern.length() + 2 && idx < rangeCount; ++i) {
            if (startMask.get(i)) {
                positions.add(i + 1);
                ++idx;
            }
        }
        return positions;
    }

    static void setBitForChar(int bit, char c) {
        mask[c - 'a'].set(bit);
    }

    static void unsetBitForChar(int bit, char c) {
        mask[c - 'a'].clear(bit);
    }

    static void update(int idx, char ch) {
        unsetBitForChar(idx, text.charAt(idx));
        text = text.substring(0, idx) + ch + text.substring(idx + 1);
        setBitForChar(idx, text.charAt(idx));
    }
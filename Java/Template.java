
import java.io.*;
import java.util.*;
import java.util.function.BinaryOperator;

public class Template {

    // static FastReader en = new FastReader();
    static FastWriter sa = new FastWriter();
    static InputReader en = new InputReader();

    static void solve() throws IOException {

    }

    public static void main(String[] args) throws IOException {
        long t;
        t = 1;
        while (t-- > 0) {
            solve();
        }
        sa.close();

    }

    public static double log2(int x) {
        return Math.log(x) / Math.log(2);
    }

    static void sort(int[] x) {
        shuffle(x);
        Arrays.sort(x);
    }

    static void sort(Object[] x) {
        shuffle(x);
        Arrays.sort(x);
    }

    static void sort(long[] x) {
        shuffle(x);
        Arrays.sort(x);
    }

    static void shuffle(int[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            int temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    static void shuffle(Object[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            int temp = (int) a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    static void shuffle(long[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            long temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    static int lower_bound(List<Integer> a, long x) {
        int l = -1, r = a.size();
        while (l + 1 < r) {
            int m = (l + r) >>> 1;
            if (a.get(m) >= x)
                r = m;
            else
                l = m;
        }
        return r;
    }

    static int upper_bound(List<Integer> a, int x) {
        int l = -1, r = a.size();
        while (l + 1 < r) {
            int m = (l + r) >>> 1;
            if (a.get(m) <= x)
                l = m;
            else
                r = m;
        }
        return l + 1;
    }

    static class FastWriter {

        private final BufferedWriter bw;

        public FastWriter() {
            this.bw = new BufferedWriter(new OutputStreamWriter(System.out));
        }

        public void print(Object object) throws IOException {
            bw.append("" + object);
        }

        public void println(Object object) throws IOException {
            print(object);
            bw.append("\n");
        }

        public void close() throws IOException {
            bw.close();
        }
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }

    }

    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        private SpaceCharFilter filter;
        private BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        public InputReader() {
            this.stream = System.in;
        }

        public int read() {
            if (numChars == -1)
                throw new InputMismatchException();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }

                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }

        public String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }

        public int nextInt() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public long nextLong() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            long res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public double nextDouble() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            double res = 0;
            while (!isSpaceChar(c) && c != '.') {
                if (c == 'e' || c == 'E')
                    return res * Math.pow(10, nextInt());
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            }
            if (c == '.') {
                c = read();
                double m = 1;
                while (!isSpaceChar(c)) {
                    if (c == 'e' || c == 'E')
                        return res * Math.pow(10, nextInt());
                    if (c < '0' || c > '9')
                        throw new InputMismatchException();
                    m /= 10;
                    res += (c - '0') * m;
                    c = read();
                }
            }
            return res * sgn;
        }

        public String readString() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        public boolean isSpaceChar(int c) {
            if (filter != null)
                return filter.isSpaceChar(c);
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public String next() {
            return readString();
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);
        }

        int[] leerArray(int n) {
            int res[] = new int[n];
            for (int i = 0; i < n; i++) {
                res[i] = nextInt();
            }
            return res;
        }

        long[] leerLongArray(int n) {
            long res[] = new long[n];
            for (int i = 0; i < n; i++) {
                res[i] = nextLong();
            }
            return res;
        }
    }

    static class SegmentTree<T> {
        int n;
        ArrayList<T> st;
        T neutro;
        BinaryOperator<T> oper;
        TreeMap<T, Integer> freq;

        SegmentTree(ArrayList<T> a, BinaryOperator<T> op, T neutro) {
            n = a.size();
            st = new ArrayList<>(Collections.nCopies(n * 4, null));
            this.neutro = neutro;
            oper = op;
            freq = new TreeMap<>();
            build(1, 0, n - 1, a);
        }

        void build(int v, int tl, int tr, ArrayList<T> a) {
            if (tl == tr) {
                st.set(v, a.get(tl));
                freq.put(a.get(tl), freq.getOrDefault(a.get(tl), 0) + 1);
                return;
            }
            int tm = (tr + tl) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm + 1, tr, a);

            st.set(v, oper.apply(st.get(v * 2), st.get(v * 2 + 1)));

        }

        T query(int v, int tl, int tr, int l, int r) {
            if (tl > r || tr < l)
                return neutro;
            if (l <= tl && tr <= r) {
                return st.get(v);
            }
            int tm = (tl + tr) / 2;

            return oper.apply(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
        }

        void upd(int v, int tl, int tr, int pos, T val) {

            if (tl == tr) {
                if (freq.containsKey(st.get(v))) {
                    freq.put(st.get(v), freq.get(st.get(v)) - 1);
                }
                st.set(v, val);
                freq.put(val, freq.getOrDefault(val, 0) + 1);
                return;
            }
            int tm = (tr + tl) / 2;
            if (pos <= tm)
                upd(v * 2, tl, tm, pos, val);
            else
                upd(v * 2 + 1, tm + 1, tr, pos, val);
            st.set(v, oper.apply(st.get(v * 2), st.get(v * 2 + 1)));

        }

        void upd(int pos, T val) {
            upd(1, 0, n - 1, pos, val);
        }

        T query(int l, int r) {
            return query(1, 0, n - 1, l, r);
        }

        int getMinFrequency(int l, int r) {
            T min = query(l, r);
            return freq.getOrDefault(min, 0);
        }
    }

    /*
     * Example
     * 
     * inicializar
     * 
     * ArrayList<Long> arr = new ArrayList<>();
     * BinaryOperator<Long> f = (a, b) -> Math.min(a, b);
     * Long neutro = Long.valueOf(1000000007);
     * SegmentTree<Long> st = new SegmentTree<Long>(arr, f, neutro);
     * 
     * 
     * 
     * while (m-- > 0) {
     * int o = en.nextInt(), l = en.nextInt(), r = en.nextInt();
     * if (o == 1) {
     * Long aux = (long) r;
     * st.upd(l, aux);
     * } else {
     * r--;
     * Long qu = st.query(l, r);
     * sa.println(qu == null ? 0 : qu);
     * }
     * }
     */

}

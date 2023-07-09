import java.io.*;
import java.util.*;

public class Template {

    static final FastWriter sa = new FastWriter();
    static final FastReader en = new FastReader();
    // static final PrintWriter pw = new PrintWriter(System.out);

    static void solve() throws IOException {
        int  n = en.nextInt();
        sa.println(n);
    }

    public static void main(String[] args) throws IOException {
        long t = 1;
        // t = en.nextLong();
        while (t-- > 0) {
            solve();
        }
        sa.close();
        // pw.close();
    }

    static long gcd(long a, long b) {
        return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
    }

    static long lcm(long a, long b) {
        long lcm = (a / gcd(a, b)) * b;
        return lcm > 0 ? lcm : -lcm;
    }

    static double log(int x) {
        /*
         * number of digits = log10(x) + 1
         * number of bits = log2(x) + 1
         * number of times that we have to divide x by k = logk(x)
         */
        // ==== log(x) / log(base);
        return Math.log(x) / Math.log(10);
    }

    static void sort(int[] x) {
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

    

    static void shuffle(long[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            long temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    static int lower_bound(List<Long> a, long x) {
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

    static int upper_bound(List<Long> a, long x) {
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

    static class pair<FIRST extends Comparable<FIRST>, SECOND extends Comparable<SECOND>>
            implements Comparable<pair<FIRST, SECOND>> {

        public final FIRST first;
        public final SECOND second;

        private pair(FIRST first, SECOND second) {
            this.first = first;
            this.second = second;
        }

        public static <FIRST extends Comparable<FIRST>, SECOND extends Comparable<SECOND>> pair<FIRST, SECOND> of(
                FIRST first, SECOND second) {
            return new pair<>(first, second);
        }

        @SuppressWarnings("NullableProblems")
        @Override
        public int compareTo(pair<FIRST, SECOND> o) {
            int cmp = compare(first, o.first);
            return cmp == 0 ? compare(second, o.second) : cmp;
        }

        private <T extends Comparable<T>> int compare(T o1, T o2) {
            if (o1 == null) {
                if (o2 == null) {
                    return 0;
                } else {
                    return -1;
                }
            } else if (o2 == null) {
                return +1;
            } else {
                return o1.compareTo(o2);
            }
        }

        @Override
        public int hashCode() {
            return 31 * hashcode(first) + hashcode(second);
        }

        private static int hashcode(Object o) {
            return o == null ? 0 : o.hashCode();
        }

        @Override
        public boolean equals(Object obj) {
            if (!(obj instanceof pair)) {
                return false;
            }
            if (this == obj) {
                return true;
            }
            return equal(first, ((pair) obj).first)
                    && equal(second, ((pair) obj).second);
        }

        private boolean equal(Object o1, Object o2) {
            return o1 == null ? o2 == null : (o1 == o2 || o1.equals(o2));
        }

        @Override
        public String toString() {
            return "(" + first + ", " + second + ')';
        }
    }

}
import static java.lang.Math.*;
import java.util.*;
import java.io.*;

public class Template {

    static FastReader en = new FastReader();
    static PrintWriter sa = new PrintWriter(System.out);

    static void solve() throws IOException {

        

    }

    public static void main(String[] args) throws IOException {
        long t = 1;
        // t = en.nextLong();
        while (t-- > 0) {
            solve();
        }
        sa.close();
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

    static void shuffle(int[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            int temp = a[i];
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

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        /*
         * FILE I/O
         * BufferedReader br = new BufferedReader(new FileReader("input.txt"));
         * PrintWriter pw = new PrintWriter(new BufferedWriter(new
         * FileWriter("output.txt")));
         * en.br = br;
         */

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

}
import static java.lang.Math.*;
import java.util.*;
import java.io.*;

public class Template {

    static FastReader en = new FastReader();
    static BufferedWriter sa = new BufferedWriter(new OutputStreamWriter(System.out));

    static void solve() throws IOException {
        //en = new FastReader("input.txt");
        //sa = new BufferedWriter(new BufferedWriter(new FileWriter("output.txt")));

        

    }

    public static void main(String[] args) throws IOException {
        long t = 1;
        // t = en.nextLong();
        while (t-- > 0) {
            solve();
        }
        en.br.close();
        sa.close();
    }
    /*
     * number of digits = log10(x) + 1
     * number of bits = log2(x) + 1
     * number of times that we have to divide x by k = logk(x)
     */

    // ==== log(x) / log(base);

    static int gcd(int a, int b) {
        return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
    }

    static int lcm(int a, int b) {
        int lcm = (a / gcd(a, b)) * b;
        return lcm > 0 ? lcm : -lcm;
    }

    static void sort(int[] a) {
        Random get = new Random();
        for (int i = 0; i < a.length; i++) {
            int r = get.nextInt(a.length);
            int temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
        Arrays.sort(a);
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        // Entrada standar
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        // Entrada por archivo
        public FastReader(String file) throws IOException {
            this.br = new BufferedReader(new FileReader(file));
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
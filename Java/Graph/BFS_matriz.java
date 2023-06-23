
import java.io.*;
import java.util.*;

public class BFS_matriz {

    static FastWriter sa = new FastWriter();
    static InputReader en = new InputReader();

    /*
     *    https://cses.fi/problemset/task/1193/
     *    un mapa en forma de matriz, llegar desde A hasta B
     */
    static class pair<T> {
        T first;
        T second;
        public pair(T f, T s) {
            first = f;
            second = s;
        }
    }

    static final int MAX_N = 1001;
    static boolean vis[][] = new boolean[MAX_N][MAX_N];
    static char ar[][] = new char[MAX_N][MAX_N];
    static char br[][] = new char[MAX_N][MAX_N];
    static LinkedList<Character> path = new LinkedList<>();
    static int n, m;
    
    static boolean isValid(int x, int y) {
        if (x < 1 || x > n || y < 1 || y > m) return false;
        if (ar[x][y] == '#' || vis[x][y]==true) return false;
        return true;
    }
    
    static boolean bfs(int x, int y) {
        LinkedList<pair<Integer>> q = new LinkedList<>();
        q.add(new pair<Integer>(x, y));
        vis[x][y] = true;

        while (!q.isEmpty()) {
            int a = q.getFirst().first;
            int b = q.getFirst().second;
            q.removeFirst();
            if(ar[a][b] == 'B'){
                while(true){
                    path.add(br[a][b]);
                    if(path.getLast() == 'L') b++;
                    if(path.getLast() == 'R') b--;
                    if(path.getLast() == 'U') a++;
                    if(path.getLast() == 'D') a--;

                    if(a==x && b==y) break;
                }
                return true;
            }
            //left
		    if(isValid(a , b - 1)){
                br[a][b-1] = 'L';
                q.add(new pair<Integer>(a, b-1));
                vis[a][b-1] = true;
            } 
		
		    //right
		    if(isValid(a , b + 1)){
                br[a][b+1] = 'R';
                q.add(new pair<Integer>(a, b+1));
                vis[a][b+1] = true;
            } 
		
		    //up
		    if(isValid(a - 1, b)) {
                br[a - 1][b] = 'U';
                q.add(new pair<Integer>(a-1, b));
                vis[a-1][b] = true;
            }
            
		
		    //down
		    if(isValid(a + 1, b)){
                br[a + 1][b] = 'D';
                q.add(new pair<Integer>(a+1, b));
                vis[a+1][b] = true;
            } 

        }
        return false;

    }

    static void solve() throws IOException {
        n = en.nextInt();
        m = en.nextInt();

        int x= 0, y= 0;
        for (int i = 1; i <= n; i++) {
            String line = en.next();
            for (int j = 1; j <= m; j++) {
                ar[i][j] =line.charAt(j-1);
                if(ar[i][j]=='A') {
                    x=i;
                    y=j;
                }
            }
        }
        if(bfs(x, y)){
            sa.println("YES\n"+path.size());
            StringBuilder ans = new StringBuilder();
            while(!path.isEmpty()) ans.append(path.removeLast());
            sa.println(ans);
        }else sa.println("NO");
        
    }

    public static void main(String[] args) throws IOException {
        long t;
        t = 1;
        while (t-- > 0) {
            solve();
        }
        sa.close();

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

}

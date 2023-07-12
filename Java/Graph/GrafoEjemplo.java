
import java.io.*;
import java.util.*;

public class GrafoEjemplo {

    // static FastReader en = new FastReader();
    static FastWriter sa = new FastWriter();
    static InputReader en = new InputReader();


    /*
     * https://codeforces.com/contest/1843/problem/D
     *  Grafo y dfs
     */
    
    static int dfs(int n, int p){
        for (int i : graph[n]) {
            if(i==p) continue;
            count[n] += dfs(i, n);
        }
        count[n] = Math.max(count[n], 1);
        return count[n];
    }

    static ArrayList<Integer> graph[];
    static int count [];

    static void solve() throws IOException {
        int n = en.nextInt();
        graph = new ArrayList [n+1];
        count = new int[n+1];

        for (int i = 0; i < n+1; i++) graph[i] = new ArrayList<>();
        
        for (int i = 1; i < n; i++) {
            int l = en.nextInt(), r = en.nextInt();
            graph[l].add(r);
            graph[r].add(l);
        }

        dfs(1, 0);

        int q = en.nextInt();
        long x = 0;
        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < q; i++) {
            int l = en.nextInt(), r = en.nextInt();
            x = count[l];
            x *= count[r];
            ans.append(x);
            ans.append('\n');
        }
        sa.print(ans);

    }

    public static void main(String[] args) throws IOException {
        long t;
        t = en.nextLong();
        while (t-- > 0) {
            solve();
        }
        sa.close();

    }

    

    

}

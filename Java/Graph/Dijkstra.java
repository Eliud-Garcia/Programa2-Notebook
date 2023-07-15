import java.util.*;

public class Dijkstra {

    static class Pair {
        int first;
        int second;

        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public String toString() {
            return "(" + first + " , " + second + ")";
        }
    }

    static final int MAXN = 100003;
    static final int INF = Integer.MAX_VALUE;

    static List<List<Pair>> adjList;
    static int n;
    static int[] dist = new int[MAXN];
    static int[] par = new int[MAXN];
    static BitSet isDone = new BitSet(MAXN);

    // dijkstra(int source, int des)
    static boolean dijkstra(int s, int t) {
        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(p -> p.first));
        Arrays.fill(dist, INF);

        pq.add(new Pair(0, s));
        dist[s] = 0;
        par[s] = -1;

        while (!pq.isEmpty()) {
            int u = pq.poll().second;

            if (u == t)
                return true;

            isDone.set(u, true);

            for (Pair pr : adjList.get(u)) {
                int v = pr.first;
                int w = pr.second;

                if (!isDone.get(v) && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.add(new Pair(dist[v], v));
                    par[v] = u;
                }
            }
        }

        return false;
    }


    /*      Dijkstra
     *      shortest path undirected graph
     *      https://codeforces.com/contest/20/problem/C
     */

    static void solve() throws IOException {
        n = en.nextInt();
        int m = en.nextInt();

        adjList = new ArrayList<>(n + 3);
        for (int i = 0; i < n + 3; i++) {
            adjList.add(new ArrayList<>());
        }

        dist = new int[MAXN];
        par = new int[MAXN];
        isDone = new BitSet(MAXN);

        int u, v, w;
        for (int i = 0; i < m; i++) {
            u = en.nextInt();
            v = en.nextInt();
            w = en.nextInt();
            adjList.get(u).add(new Pair(v, w));
            adjList.get(v).add(new Pair(u, w));
        }
        //path is found
        if (dijkstra(1, n)) {
            StringBuilder ans = new StringBuilder();
            List<Integer> path = new ArrayList<>();
            for (v = n; v != -1; v = par[v]) {
                path.add(v);
            }
            //reversing path
            for (int i = path.size()-1; i >=0; i--) {
                ans.append(path.get(i)).append(" ");
            }
            sa.println(ans);
        } else {
            sa.println("-1");
        }
    }
}


    static final int INF = Integer.MAX_VALUE;
    static List<int[]> adj[];
    static int[] dist;
    static int[] par;
    static BitSet isDone;

    // dijkstra(int source, int des)
    static boolean dijkstra(int s, int t) {

        // new int[] {destino, peso};
    
        Comparator<int[]> cmp = new Comparator<int[]>() {
            @Override
            public int compare(int a[], int b[]) {
                return Integer.compare(a[0], b[0]);
            }
        };

        PriorityQueue<int[]> pq = new PriorityQueue<>(cmp);

        Arrays.fill(dist, INF);

        pq.add(new int[] { 0, s });

        dist[s] = 0;
        par[s] = -1;

        while (!pq.isEmpty()) {
            int u = pq.poll()[1];

            if (u == t) return true;

            isDone.set(u, true);

            for (int[] next : adj[u]) {
                int v = next[0];
                int w = next[1];

                if (!isDone.get(v) && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.add(new int[] { dist[v], v });
                    par[v] = u;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        int n = nextInt();
        int m = nextInt();

        adj = new ArrayList[n + 3];
        dist = new int[n + 3];
        par = new int[n + 3];
        isDone = new BitSet(n + 3);


        for (int i = 0; i < n + 3; i++){
            adj[i] = new ArrayList<>();
        }

        int a, b, w;
        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            w = nextInt();

            //adj[source].add(new int[] {dest, weight});
            adj[a].add(new int[] { b, w });
            adj[b].add(new int[] { a, w });
        }

        // path is found
        if (dijkstra(1, n)) {
            StringBuilder ans = new StringBuilder();
            List<Integer> path = new ArrayList<>();

            for (b = n; b != -1; b = par[b]) path.add(b);

            // reversing path
            for (int i = path.size() - 1; i >= 0; i--) {
                ans.append(path.get(i) + " ");
            }
            sa.println(ans);
        } else {
            sa.println("-1");
        }
        sa.close();
    }


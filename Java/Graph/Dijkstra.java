
    static final long INF = Long.MAX_VALUE;
    static List<edge> g[];
    static long dis[];
    static int par[];
    static boolean vis[];

    static class edge {
        int v;
        long w;

        edge(int node, long weight) {
            v = node;
            w = weight;
        }
    }

    // dijkstra(int source, int des)
    static boolean dijkstra(int s, int t) {

        Comparator<edge> cmp = new Comparator<edge>() {
            @Override
            public int compare(edge a, edge b) {
                return Long.compare(a.w, b.w);
            }
        };

        PriorityQueue<edge> pq = new PriorityQueue<>(cmp);
        Arrays.fill(dis, INF);

        // new edge(node, weight);
        pq.add(new edge(s, 0));

        dis[s] = 0;
        par[s] = -1;

        while (!pq.isEmpty()) {
            edge x = pq.poll();
            int u = x.v;

            if (u == t) {
                return true;
            }

            vis[u] = true;

            for (edge next : g[u]) {
                int v = next.v;
                long w = next.w;

                if (!vis[v] && dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    pq.add(new edge(v, dis[v]));
                    par[v] = u;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        int n = nextInt();
        int m = nextInt();

        g = new ArrayList[n + 3];
        dis = new long[n + 3];
        par = new int[n + 3];
        vis = new boolean[n + 3];

        for (int i = 0; i < n + 3; i++) {
            g[i] = new ArrayList<>();
            dis[i] = INF;
        }

        int a, b;
        long w;
        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            w = nextLong();

            // adj[source].add({dest, weight});
            g[a].add(new edge(b, w));
            g[b].add(new edge(a, w));
        }

        // path is found
        if (dijkstra(1, n)) {
            StringBuilder ans = new StringBuilder();
            List<Integer> path = new ArrayList<>();

            for (b = n; b != -1; b = par[b])
                path.add(b);

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

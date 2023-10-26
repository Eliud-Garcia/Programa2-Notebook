
    // Finding bridges in a graph in O(N+M)
    // undirected graph.
    //given a map of cities connected with roads, find all "important" roads

    static int n, m, q;
    static List<Integer> g[];
    static boolean vis[];
    static int tin[], low[], parent[];
    static int timer;
    static int bridges;

    static void dfs(int node, int par) {
        vis[node] = true;
        tin[node] = low[node] = timer++;
        for (int next : g[node]) {
            if (next == par)
                continue;
            if (vis[next]) {
                low[node] = min(low[node], tin[next]);
            } else {
                dfs(next, node);
                low[node] = min(low[node], low[next]);
                if (low[next] > tin[node]) {
                    // IS_BRIDGE(v, to);
                    sa.println(node +" "+ next);
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        n = nextInt();
        m = nextInt();

        g = new List[n + 1];
        vis = new boolean[n + 1];
        tin = new int[n + 1];
        low = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            g[i] = new ArrayList<>();
            tin[i] = -1;
            low[i] = -1;
        }
        int a, b;
        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            g[a].add(b);
            g[b].add(a);
        }
        
        sa.println("bridges");
        for (int j = 1; j <= n; j++) {
            if (!vis[j]) {
                dfs(j, -1);
            }
        }
        

        sa.close();
    }

// Tarjan's Algorithm
// Finding bridges in a graph in O(N + M)
// Undirected graph.
static List<Integer> g[];
static int tin[], low[];
static int timer = 0;
static List<int[]> bridges;
static boolean is_articulation[], vis[];

static void dfs(int v, int p) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int u : g[v]) {
        if (u == p) continue;
        if (vis[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] >= tin[v] && p != -1)
                is_articulation[v] = true;
            ++children;
            if (low[u] > tin[v])
                bridges.add(new int[] { v, u });
        }
    }
    if (p == -1 && children > 1)
        is_articulation[v] = true;
}
static int n, m;
public static void main(String[] args) {
    n = nextInt();
    m = nextInt();
    g = new List[n + 1];
    tin = new int[n + 1];
    low = new int[n + 1];
    vis = new boolean[n + 1];
    is_articulation = new boolean[n + 1];
    bridges = new ArrayList<>();
    Arrays.setAll(g, i -> new ArrayList<>());
    int a, b;
    for (int i = 0; i < m; i++) {
        a = nextInt();
        b = nextInt();
        g[a].add(b);
        g[b].add(a);
    }
    // find bridges and articulation points
    for (int i = 1; i <= n; i++) {
        if(!vis[i]){
            dfs(i, -1);
        }
    }
    // print articulation points
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) {
            sa.print(i + "\n");
        }
    }
    // print bridges
    for (int[] i : bridges) {
        sa.print(i[0] + "-" + i[1] + "\n");
    }
    sa.close();
}
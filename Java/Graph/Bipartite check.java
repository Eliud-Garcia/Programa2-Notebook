static List<Integer> graph[];
static boolean vis[];
static int parent[];
static int n, m;
static int color[];
static ArrayList<Integer> ans[] = new ArrayList[3];
static boolean bipartite = true;
static void dfs(int node, int curColor) {
    vis[node] = true;
    color[node] = curColor;
    ans[curColor].add(node);
    for (int next : graph[node]) {
        if (!vis[next]) {
            if (curColor == 1) {
                color[next] = 2;
                dfs(next, 2);
            } else {
                color[next] = 1;
                dfs(next, 1);
            }
        }
        if (color[next] == color[node]) {
            bipartite = false;
            return;
        }
    }
}
public static void main(String[] args) throws IOException {
    n = nextInt();
    m = nextInt();
    graph = new List[n + 1];
    vis = new boolean[n + 1];
    color = new int[n + 1];
    ans[1] = new ArrayList<>();
    ans[2] = new ArrayList<>();
    for (int i = 0; i < n + 1; i++) {
        graph[i] = new ArrayList<>();
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        a = nextInt();
        b = nextInt();
        graph[a].add(b);
        graph[b].add(a);
    }
    for (int i = 1; i < n + 1 && bipartite; i++) {
        if (!vis[i]) {
            dfs(i, 1);
        }
    }
    if (!bipartite) {
        sa.println(-1);
    } else {
        //color 1
        sa.println(ans[1].size());
        for (int x : ans[1]) sa.print(x + " ");
        sa.println();

        //color 2
        sa.println(ans[2].size());
        for (int x : ans[2]) sa.print(x + " ");
        sa.println();

    }
    // sa.println(Arrays.toString(color));
    sa.close();
}

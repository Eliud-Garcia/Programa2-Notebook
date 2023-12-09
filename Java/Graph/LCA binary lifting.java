    
    //build = n log(n)
    //query = log(n)
    static int n, l, q;
    static List<Integer> tree[];
    static int timer;
    static int tin[], tout[], dis[];
    static int up[][];
 
    static void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i - 1]][i - 1];
        for (int u : tree[v]){
            if (u != p){
                dis[u] = dis[v] + 1;
                dfs(u, v);
            }
        }
        tout[v] = ++timer;
    }
 
    static boolean is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
 
    static int lca(int u, int v) {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)){
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    public static void main(String[] args) {
        n = nextInt();
        q = nextInt();
        tree = new List[n + 1];
        tin = new int[n + 1];
        tout = new int[n + 1];
        dis = new int[n + 1];
        timer = 0;
        l = (int) ceil(log(n + 1) / log(2));
        up = new int[n + 1][l + 1];

        Arrays.setAll(tree, i -> new ArrayList<>());
        int a, b;
        for (int i = 0; i < n - 1; i++) {
            a = nextInt();
            b = nextInt();
            tree[a].add(b);
            tree[b].add(a);
        }
        dfs(1, 1);
        while (q-- > 0) {
            a = nextInt();
            b = nextInt();
            //distancia entre a y b
            sa.print(dis[a] + dis[b] - (2 * dis[lca(a, b)]) + "\n");
        }

        sa.close();
    }

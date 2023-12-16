

    //build = n log(n)
    //query = log(n)
    
    static int n, log, q;
    static List<Integer> tree[];
    static int depth[];
    static int up[][];

    static void dfs(int node, int p, int d) {
        up[0][node] = p;
        depth[node] = d;
        for (int u : tree[node]) {
            if (u == p)
                continue;
            depth[u] = depth[node] + 1;
            dfs(u, node, d + 1);
        }
    }

    static void build(int n) {
        for (int a[] : up) {
            Arrays.fill(a, -1);
        }
        dfs(1, 1, 0);
        for (int i = 1; i < log; i++) {
            for (int u = 0; u < n; u++) {
                if (up[i - 1][u] != -1) {
                    up[i][u] = up[i - 1][up[i - 1][u]];
                }
            }
        }
    }

    static int lca(int u, int v) {
        if (depth[u] > depth[v]) {
            int x = u;
            u = v;
            v = x;
        }
        int dis = depth[v] - depth[u];
        for (int i = log - 1; i >= 0; i--) {
            if (((dis >> i) & 1) == 1) {
                v = up[i][v];
            }
        }
        if (u == v)
            return u;
        for (int i = log - 1; i >= 0; i--) {
            if (up[i][v] != up[i][u]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][v];
    }

    public static void main(String[] args) {
        n = nextInt();
        tree = new List[n + 1];
        depth = new int[n + 1];
        log = (int) (ceil(log(n + 1) / log(2)));
        up = new int[log + 1][n + 1];
        Arrays.setAll(tree, i -> new ArrayList<>());

        int a, b, c;
        for (int i = 0; i < n - 1; i++) {
            a = nextInt();
            b = nextInt();
            tree[a].add(b);
            tree[b].add(a);
        }
        build(n + 1);
        q = nextInt();
        while (q-- > 0) {
            a = nextInt();
            b = nextInt();
            c = nextInt();
            int ancestor = lca(a, b);
            int disAB = depth[a] + depth[b] - (2 * depth[ancestor]);
            int disA_lca = depth[a] - depth[ancestor];
            if (disAB <= c) {
                sa.print(b + "\n");
            } else {
                if (disA_lca >= c) {
                    //nos acercamos dando brincos
                    //en potencias de 2
                    for (int k = log; k >= 0; k--) {
                        if (((c >> k) & 1) == 1) {
                            a = up[k][a];
                        }
                    }
                    sa.print(a + "\n");
                } else {
                    int df = disAB - c;
                    for (int k = log; k >= 0; k--) {
                        if (((df >> k) & 1) == 1) {
                            b = up[k][b];
                        }
                    }
                    sa.print(b + "\n");
                }
            }
        }

        sa.close();
    }
    //https://codeforces.com/gym/102694/problem/C/

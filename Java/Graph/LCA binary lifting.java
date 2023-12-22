

    //build = n log(n)
    //query = log(n)
    
    static int n, m, q, log;
    static List<Integer> g[];
    static List<Integer> projects[];
    static int deep[];
    //static int times[]; // tiempo de descubrir el nodo en el dfs
    static int up[][];
    static int cnt = 1;

    static void dfs(int u, int p) {
        for (int v : g[u]) {
            if (v != p){
                deep[v] = deep[u] + 1;
                up[0][v] = u;
                //times[v] = cnt++;
                dfs(v, u);
            } 
        }
    }

    static void build(int n, int root) {
        dfs(root, root);
        for (int i = 1; i <= log; i++) {
            for (int u = 1; u < n; u++) {
                if (up[i - 1][u] != -1) {
                    up[i][u] = up[i - 1][up[i - 1][u]];
                }
            }
        }
    }

    static int lca(int u, int v) {
        if (deep[u] > deep[v]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        int diff = deep[v] - deep[u];
        for (int i = log - 1; i >= 0; i--) {
            if((diff & (1 << i)) !=0){
                v = up[i][v];
            }
        }
        if (u == v) return u;
        for (int i = log - 1; i >= 0; i--) {
            if (up[i][v] != up[i][u]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    }

    public static void main(String[] args) {
        n = nextInt();
        g = new List[n + 1];
        deep = new int[n + 1];
        log = (int) (ceil(log(n + 1) / log(2)));
        up = new int[log + 1][n + 1];
        Arrays.setAll(g, i -> new ArrayList<>());
 
        int a, b, c;
        for (int i = 0; i < n - 1; i++) {
            a = nextInt();
            b = nextInt();
            g[a].add(b);
            g[b].add(a);
        }
        int root = 1;
        build(n + 1, root);
        q = nextInt();
        while (q-- > 0) {
            a = nextInt();
            b = nextInt();
            c = nextInt();
            int ancestor = lca(a, b);
            int disAB = deep[a] + deep[b] - (2 * deep[ancestor]);
            int disA_lca = deep[a] - deep[ancestor];
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

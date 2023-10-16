   
    // Lowest Common Ancestor
    // Se usa el Euler tour para encontrar un nodo que
    // está entre u y v que tiene la altura mas baja

    static class LCA {
        int height[], first[];
        int st[]; // Sparse Table
        List<Integer> euler;
        boolean vis[];
        int n;

        LCA(List<Integer> g[], int root) {
            n = g.length;
            height = new int[n];
            vis = new boolean[n];
            first = new int[n];
            euler = new ArrayList<>(Collections.nCopies(n * 2, 0));
            dfs(g, root, 0);

            int m = euler.size();
            st = new int[m * 4];
            build(1, 0, m - 1);

        }

        void dfs(List<Integer> g[], int node, int h) {
            vis[node] = true;
            height[node] = h;
            first[node] = euler.size();
            euler.add(node);
            for (int next : g[node]) {
                if (!vis[next]) {
                    dfs(g, next, h + 1);
                    euler.add(node);
                }
            }
        }

        void build(int node, int b, int e) {
            if (b == e) {
                st[node] = euler.get(b);
            } else {
                int mid = (b + e) / 2;
                build(node << 1, b, mid);
                build(node << 1 | 1, mid + 1, e);
                int l = st[node << 1], r = st[node << 1 | 1];
                st[node] = (height[l] < height[r]) ? l : r;
            }
        }

        int query(int node, int b, int e, int L, int R) {
            if (b > R || e < L)
                return -1;
            if (b >= L && e <= R)
                return st[node];
            int mid = (b + e) >> 1;

            int left = query(node << 1, b, mid, L, R);
            int right = query(node << 1 | 1, mid + 1, e, L, R);
            if (left == -1)
                return right;
            if (right == -1)
                return left;
            return height[left] < height[right] ? left : right;
        }

        int lca(int u, int v) {
            int left = first[u], right = first[v];
            if (left > right) {
                int tmp = left;
                left = right;
                right = tmp;
            }
            return query(1, 0, euler.size() - 1, left, right);
        }
    }

    public static void main(String[] args) throws IOException {

        int n = nextInt();
        List<Integer> g[] = new List[n + 1];
        for (int i = 0; i <= n; i++) {
            g[i] = new ArrayList<>();
        }
        int a, b;
        for (int i = 0; i < n-1; i++) {
            a = nextInt();
            b = nextInt();
            g[a].add(b);
            g[b].add(a);

        }
        LCA ans = new LCA(g, 1);
        int q = nextInt();
        while (q-- > 0) {
            a = nextInt();
            b = nextInt();
            sa.println(ans.lca(a, b));
        }

        sa.close();
    }


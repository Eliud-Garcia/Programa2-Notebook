// Lowest Common Ancestor
// Se usa el Euler tour para encontrar un nodo que
// está entre u y v que tiene la altura mas baja
static class LCA {
    int height[], first[];
    int st[]; // Segment Tree
    int table[][];// Sparse Table
    List<Integer> euler;// euler tour
    List<Integer> g[];
    boolean SegTree;
    int n;
    // LCA with segment tree -> option = 1
    // LCA with Sparse Table -> option = 2
    LCA(List<Integer> graph[], int root, int option) {
        n = graph.length;
        g = graph;
        height = new int[n];
        first = new int[n];
        euler = new ArrayList<>();
        dfs(root, root, 0);

        if (option == 1) {
            SegTree = true;
            int m = euler.size();
            st = new int[m * 4];
            build(1, 0, m - 1);
        } else if (option == 2) {
            SegTree = false;
            build();
        }
    }
    void dfs(int node, int p, int h) {
        height[node] = h;
        first[node] = euler.size();
        euler.add(node);
        for (int next : g[node]) {
            if (next != p) {
                dfs(next, node,  h + 1);
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
        if (b > R || e < L) return -1;
        if (b >= L && e <= R) return st[node];
        int mid = (b + e) >> 1;
        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }
    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right) {
            int tmp = left;
            left = right;
            right = tmp;
        }
        if (SegTree) {
            return query(1, 0, euler.size() - 1, left, right);
        } else {
            return query(left, right);
        }
    }
    void build() {
        int N = euler.size();
        int K = (int) ((log(N) / log(2))) + 1;
        table = new int[N + 1][K];
        for (int i = 0; i < N; i++)
            table[i][0] = euler.get(i);

        for (int j = 0; j < K - 1; j++) {
            for (int i = 0; i + (1 << (j + 1)) <= N; ++i) {
                int a = table[i][j];
                int b = table[i + (1 << j)][j];
                table[i][j + 1] = height[a] < height[b] ? a : b;
            }
        }
    }
    int query(int l, int r) {
        int k = 31 - Integer.numberOfLeadingZeros(r - l + 1);
        int a = table[l][k];
        int b =  table[r - (1 << k) + 1][k];
        return height[a] < height[b] ? a : b;
    }
}

public static void main(String[] args) throws IOException {
    int n = nextInt();
    int q = nextInt();
    List<Integer> g[] = new List[n + 1];
    Arrays.setAll(g, i -> new ArrayList<>());
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        a = nextInt();
        b = nextInt();
        g[a].add(b);
        g[b].add(a);
    }
    LCA lca = new LCA(g, 1, 2);
    while (q-- > 0) {
        a = nextInt();
        b = nextInt();
        int LCA = lca.lca(a, b);
        sa.print(lca.height[a] + lca.height[b] - (2 * lca.height[LCA]) + "\n");
    }

    sa.close();
}

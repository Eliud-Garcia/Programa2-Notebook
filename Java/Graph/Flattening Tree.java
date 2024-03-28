static List<Integer> tree[];
static int tin[];
static int tout[];
static long aplanado[];
static int n, q;
static int timer = 0;
// dfs para aplanar O(n)
static void dfs(int node, int parent) {
    tin[node] = timer;
    // aplanado[timer] = node; normalmente
    // en este caso toca trabajar sobre el color
    aplanado[timer] = color[node]; 
    timer++;
    for (int next : tree[node]) {
        if (next != parent) {
            dfs(next, node);
        }
    }
    tout[node] = timer - 1;
}
// Ejemplo de uso
//https://codeforces.com/contest/620/problem/E
static int color[];
public static void main(String[] args) {
    n = nextInt();
    q = nextInt();
    tree = new List[n + 1];
    tin = new int[n + 1];
    tout = new int[n + 1];
    aplanado = new long[n + 1];
    Arrays.setAll(tree, i -> new ArrayList<>());
    color = new int[n + 1];
    for (int i = 1; i <= n; i++) {
        int x = nextInt();
        color[i] = x;
    }
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        a = nextInt();
        b = nextInt();
        tree[a].add(b);
        tree[b].add(a);
    }
    dfs(1, 0);
    // sa.print(Arrays.toString(aplanado)+"\n");
    // sa.print(Arrays.toString(tin)+"\n");
    // sa.print(Arrays.toString(tout)+"\n");
    SegmentreeLazy st = new SegmentreeLazy(aplanado, 0L);
    int oper, v, c;
    while (q-- > 0) {
        oper = nextInt();
        if (oper == 1) {
            v = nextInt();
            c = nextInt();
            // l = timepoEntrada
            // r = tiempoSalida
            // (tin[v], tout[v]) = subArbol del nodo v
            st.upd(tin[v], tout[v], c);
        } else {
            v = nextInt();
            long ans = st.query(tin[v], tout[v]);
            sa.print(Long.bitCount(ans) + "\n");
        }
    }
    sa.close();
}
//SegTree Lazy para contar colores diferentes en un rango (subArbol)
static class SegmentreeLazy {
    int n;
    long st[], lazy[];
    long neutro;
    long oper(long a, long b) {
        return a | b;
    }
    SegmentreeLazy(int m, long neutro) {
        n = m;
        st = new long[n * 4];
        lazy = new long[n * 4];
        this.neutro = neutro;
    }
    SegmentreeLazy(long a[], long neutro) {
        n = a.length;
        st = new long[n * 4];
        lazy = new long[n * 4];
        build(1, 0, n - 1, a);
    }
    void build(int v, int tl, int tr, long a[]) {
        if (tl == tr) {
            st[v] = 1L << a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }
    void push(int v, int tl, int tr) {
        if (lazy[v] <= 0)
            return;
        // st[v] += (tr - tl + 1) * lazy[v];
        st[v] = 1L << lazy[v];
        if (tl != tr) {
            // lazy[v * 2] += lazy[v];
            // lazy[v * 2 + 1] += lazy[v];
            lazy[v * 2] = lazy[v * 2 + 1] = lazy[v];
        }
        lazy[v] = 0;
    }
    void upd(int v, int tl, int tr, int l, int r, long val) {
        push(v, tl, tr);
        if (tr < l || tl > r)
            return;
        if (tl >= l && tr <= r) {
            lazy[v] = val;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm + 1, tr, l, r, val);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }
    long query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (tl > r || tr < l)
            return neutro;
        if (l <= tl && tr <= r)
            return st[v];
        int tm = (tl + tr) / 2;
        return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
    }
    // l inclusive r inclusive
    // [l, r]
    void upd(int l, int r, long val) {
        upd(1, 0, n - 1, l, r, val);
    }

    long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

}

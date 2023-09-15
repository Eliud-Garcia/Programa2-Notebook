
//permite procesar consultas rangos y actualizaciones por rangos sobre un arreglo.

static class SegmentreeLazy {
    int n;
    long st[], lazy[];
    long neutro;

    // definir operacion
    long oper(long a, long b) {
        return a + b;
    }

    SegmentreeLazy(int m, long neutro) {
        n = m;
        st = new long[n * 4];
        lazy = new long[n * 4];
        this.neutro = neutro;

    }

    SegmentreeLazy(List<Long> a, long neutro) {
        n = a.size();
        st = new long[n * 4];
        lazy = new long[n * 4];
        build(1, 0, n - 1, a);
    }

    void build(int v, int tl, int tr, List<Long> a) {
        if (tl == tr) {
            st[v] = a.get(tl);
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
        st[v] += (tr - tl + 1) * lazy[v];
        if (tl != tr) {
            lazy[v * 2] += lazy[v];
            lazy[v * 2 + 1] += lazy[v];
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

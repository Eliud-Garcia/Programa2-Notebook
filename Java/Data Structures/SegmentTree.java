//indexado desde 0 
static class SegTree {
    int n;
    long st[];
    long neutro;
    SegTree(long a[], long neutro) {
        n = a.length;
        st = new long[n * 4];
        this.neutro = neutro;

        build(1, 0, n - 1, a);
    }
    long oper(long a, long b) {
        return min(a, b);
    }
    void build(int v, int tl, int tr, long a[]) {
        if (tl == tr) {
            st[v] = a[tl];
            return;
        }
        int tm = (tr + tl) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }
    long query(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l)
            return neutro;
        if (l <= tl && tr <= r)
            return st[v];
        int tm = (tl + tr) / 2;
        return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
    }
    void upd(int v, int tl, int tr, int pos, long val) {
        if (tl == tr) {
            st[v] = val;
            return;
        }
        int tm = (tr + tl) / 2;
        if (pos <= tm)
            upd(v * 2, tl, tm, pos, val);
        else
            upd(v * 2 + 1, tm + 1, tr, pos, val);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }
    void upd(int pos, long val) {
        upd(1, 0, n - 1, pos, val);
    }
    // l inclusive r exclusive
    // indexado desde cero
    long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
}

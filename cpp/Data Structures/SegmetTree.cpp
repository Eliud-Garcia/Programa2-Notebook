template <typename T>
struct STree {
    int n;
    vector<T> st;
    T neutro = T(0);

    STree(vector<T>& a)
    {
        n = sz(a);
        st.resize(n * 4);
        build(1, 0, n - 1, a);
    }

    T oper(T a, T b) { return max(a, b); }

    void build(int v, int tl, int tr, vector<T>& a)
    {
        if (tl == tr) {
            st[v] = a[tl];
            return;
        }
        int tm = (tr + tl) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }

    T query(int v, int tl, int tr, int l, int r)
    {
        if (tl > r || tr < l)
            return neutro;
        if (l <= tl && tr <= r)
            return st[v];
        int tm = (tl + tr) / 2;
        return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
    }

    void upd(int v, int tl, int tr, int pos, T val)
    {
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

    int countQuery(int v, int tl, int tr, int l, int r, T x)
    {
        if (tl > r || tr < l)
            return 0;
        if (l <= tl && tr <= r) {
            if (st[v] <= x) {
                /*
                Para mayores st[v] <= x query max(a,b)
                Para mayores o equ st[v] < x query max(a,b)
                Para menores st[v] >= x query min(a,b)
                Para menores o equ st[v] > x query min(a,b)
                */
                return 0;
            }
            if (tl == tr)
                return 1;
        }
        int tm = (tl + tr) / 2;
        return countQuery(v * 2, tl, tm, l, r, x) + countQuery(v * 2 + 1, tm + 1, tr, l, r, x);
    }
    int countQuery(int a, int b, T x)
    {
        return countQuery(1, 0, n - 1, a, b, x);
    }
    void upd(int pos, T val) { upd(1, 0, n - 1, pos, val); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
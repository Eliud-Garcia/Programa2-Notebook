template<typename T>
struct STree {
    #define L(v) v << 1
    #define R(v) v << 1 | 1
    //L(v) = 2 * v
    //R(v) = 2 * v + 1

    int n;
    vector<T> st, lazy;
    T neutro = T(0);

    STree(int m) {
        n = m;
        st.resize(n * 4);
        lazy.resize(n * 4);
    }

    STree(vector<T> &a) {
        n = sz(a);
        st.resize(n * 4);
        lazy.resize(n * 4);
        build(1, 0, n - 1, a);
    }

    T oper(T a, T b) {
        return a + b;
    }

    void build(int v, int tl, int tr, vector<T> &a) {
        if(tl == tr) {
            st[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(L(v), tl, tm, a);
        build(R(v), tm + 1, tr, a);
        st[v] = oper(st[L(v)], st[R(v)]);
    }

    void push(int v, int tl, int tr) {
        if (!lazy[v]) return;
        st[v] += (tr - tl + 1) * lazy[v];
        if (tl != tr) {
            lazy[L(v)] += lazy[v];
            lazy[R(v)] += lazy[v];
        }
        lazy[v] = 0;
    }

    void upd(int v, int tl, int tr, int l, int r, T val) {
        push(v, tl, tr);
        if(tr < l || tl > r) return;
        if (tl >= l && tr <= r) {
            lazy[v] = val;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd(L(v), tl, tm, l, r, val);
        upd(R(v), tm + 1, tr, l, r, val);
        st[v] = oper(st[L(v)], st[R(v)]);
    }

    T query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if(tl > r || tr < l) return neutro;
        if (l <= tl && tr <= r) return st[v];
        int tm = (tl + tr) / 2;
        return oper(query(L(v), tl, tm, l, r), query(R(v), tm + 1, tr, l, r));
    }

    void upd(int l, int r, T val) {
        upd(1, 0, n - 1, l, r, val);
    }
    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

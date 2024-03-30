static class Node{
    long val;
    Node(long v){
        val = v;
    }
}
static class STree {
    int n;
    Node neutro = new Node(0);
    Node st[];
    STree(int N) {
        n = N;
        for (int i = 0; i < (1<<n); i++)
            st[i] = neutro;
    }
    STree(long a[]) {
        n = a.length;
        st = new Node[1 << n];
        build(a);
    }
    Node oper(Node a, Node b) {
        return new Node(a.val + b.val);
    }
    void build(long a[]) {
        for (int i = 0; i < n; i++)
            st[n + i] = new Node(a[i]);
        for (int i = n - 1; i >= 1; i--)
            st[i] = oper(st[i << 1], st[i << 1 | 1]);
    }
    Node query(int l, int r) { // [l, r]
        Node vl = neutro, vr = neutro;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) vl = oper(vl, st[l++]);
            if ((r & 1) == 1) vr = oper(st[--r], vr);
        }
        return oper(vl, vr);
    }
    void upd(int p, long val) { // set val at position p (0 - idx)
        for (st[p += n] = new Node(val); p > 1; p >>= 1)
            st[p >> 1] = oper(st[p], st[p ^ 1]);
    }
}
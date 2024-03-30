//segment tree almacena 
//varios valores en los nodos
static class Node{
    long val; //Stores the sum of the segment
    long suff; //Stores the maximum suffix sum of the segment
    long pref; // Stores the maximum prefix sum of the segment
    long ans;//maximum sum of the segment
    Node(long v){
        if(v < 0){
            val = v;
            suff = 0;
            suff = 0;
        }else{
            val = v;
            suff = val;
            pref = val;
            ans = val;
        } 
    }
}
static class SegTree {
    int n;
    Node st[];
    Node neutro;
    SegTree(long a[], Node neutro) {
        n = a.length;
        st = new Node[n * 4];
        this.neutro = neutro;
        build(1, 0, n - 1, a);
    }
    Node oper(Node a, Node b) {
        Node ans = new Node(0);
        ans.val = a.val + b.val;
        ans.pref = max(a.pref, a.val + b.pref);
        ans.suff = max(b.suff, b.val + a.suff);
        ans.ans = max(a.suff + b.pref, max(a.ans, b.ans));
        return ans;
    }
    void build(int v, int tl, int tr, long a[]) {
        if (tl == tr) {
            st[v] = new Node(a[tl]);
            return;
        }
        int tm = (tr + tl) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }
    Node query(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l){
            return st[v];
        }
        if (l <= tl && tr <= r)
            return st[v];
        int tm = (tl + tr) / 2;
        return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
    }
    void upd(int v, int tl, int tr, int pos, long val) {
        if (tl == tr) {
            st[v] = new Node(val);
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
    //[0, n - 1]
    Node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
}
public static void main(String[] args) {
    int n = nextInt();
    int q = nextInt();
    long a[] = new long[n];
    Arrays.setAll(a, i-> nextInt());
    SegTree st = new SegTree(a, new Node(0));
    long ans = st.st[1].ans;//raiz -> [0, n-1]
    sa.print(ans+"\n");
    while(q-->0){
        int i = nextInt();
        long val = nextLong();
        st.upd(i, val);
        ans = st.st[1].ans;
        sa.print(ans+"\n");
    }
}

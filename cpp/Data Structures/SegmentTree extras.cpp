/*
oper = a + b
obtener el k-esimo 1 o lower_bound
inicializar con 1s el vector
*/

int find_kth(int v, int tl, int tr, int k) {
    if (k > st[v])
        return -1;
    if (tl == tr)
        return tl;
    int tm = (tl + tr) / 2;
    if (st[L(v)] >= k)
        return find_kth(L(v), tl, tm, k);
    else
        return find_kth(R(v), tm + 1, tr, k - st[L(v)]);
}

/*
SegmentTree Bracket
solo es modificar lo siguiente
*/

struct node {
    int open, closed, len;
    node() : open(0), closed(0), len(0){};
    node(char c){
        len = 0;
        open = (c == '(' ? 1 : 0);
        closed = (c == ')' ? 1 : 0);
    }
};
//el neutro
T neutro = node();
//la operacion
T oper(T a, T b) {
    node ans;
    int m = min(a.open, b.closed);
    ans.len = a.len + b.len + m * 2;
    ans.open = a.open + b.open - m;
    ans.closed = a.closed + b.closed - m;
    return ans;
}
//para crearlo es en base a un string
vector<node> a(sz(s));

for(int i = 0; i < sz(s); i++){
    a[i] = node(s[i]);
}

STree<node> st(a);

//para upd
st.upd(i, node(s[i]));
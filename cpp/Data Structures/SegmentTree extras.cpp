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

/*------------------------------
STree bracket
solo es modificar lo siguiente
------------------------------*/
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

/*------------------------
para maximum subarray sum
------------------------*/
struct node {
    ll val, sf, pf, ans;
    node() : val(0), sf(0), pf(0), ans(0) {}
    node(ll v) {
        val = v;
        sf = max(v, 0LL);
        pf = max(v, 0LL);
        ans = max(v, 0LL);
    }
};
T neutro = node();

T oper(T a, T b) {
    node ans(0);
    ans.val = a.val + b.val;
    ans.pf = max(a.pf, a.val + b.pf);
    ans.sf = max(b.sf, b.val + a.sf);
    ans.ans = max(a.sf + b.pf, max(a.ans, b.ans));
    return ans;
}

vector<int> a(n);
for(int i = 0; i < n; i++) 
cin >> a[i];

vector<node> aux(n);
for(int i = 0; i < n; i++){
    aux[i] = node(a[i]);
}

STree<node> st(aux);

/*-------------------------------
para validar 
si un rangos (l, r) es palindromo
con updates 
--------------------------------*/

//#usar UnitHash de strings  
bool is_pal(int l, int r,  int n, STree<UnitHash> &h1,  STree<UnitHash> &h2) {
    return (h1.query(l, r).h == h2.query(n - r - 1, n - l - 1).h);
}
//para crear
vector<UnitHash> a(n), b(n);
forn(i, n){
    a[i] = UnitHash(s[i] * 1LL, B);
    b[n - i - 1] = UnitHash(s[i] * 1LL, B);
    //B es la base del UnitHash
}
STree<UnitHash> st1(a); //normal
STree<UnitHash> st2(b); //reverse

if(t == 1){ //update
    int i;
    char x; 
    cin >> i >> x;
    st1.upd(i - 1, UnitHash(x * 1LL, B));
    st2.upd(n - i, UnitHash(x * 1LL, B));
}else{ //query
    int l, r;
    cin >> l >> r;
    bool ans = is_pal(l - 1, r - 1, n, st1, st2);
    cout << (ans ? "YES" : "NO") << ln;
}
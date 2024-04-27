template<typename T>
struct STree {
  int n; vector<T> st;
  T neutro = T(0);
  STree(vector<T> &a) {
    n = sz(a);
    st.resize(n * 4);
    build(1, 0, n - 1, a);
  }
  T oper(T a, T b) { return max(a, b); }
  void build(int v, int tl, int tr, vector<T> &a) {
    if(tl == tr) {
      st[v] = a[tl];
      return;
    }
    int tm = (tr + tl) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm + 1, tr, a);
    st[v] = oper(st[v * 2], st[v * 2 + 1]);
  }
  T query(int v, int tl, int tr, int l, int r) {
    if(tl > r || tr < l) return neutro;
    if(l <= tl && tr <= r) return st[v];
    int tm = (tl + tr) / 2;
    return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
  }
  void nearestBiggerElem(int v, int tl, int tr, T val) {
    if(tl == tr) {
      st[v] -=val;
      cout << tl + 1 <<" ";
      return;
    }
    int tm = (tr + tl) / 2;
    if(st[v * 2] >= val) nearestBiggerElem(v * 2, tl, tm, val);
    else nearestBiggerElem(v * 2 + 1, tm + 1, tr,  val);
    st[v] = oper(st[v * 2], st[v * 2 + 1]);
  }

  void upd(int v, int tl, int tr, int pos, T val) {
    if(tl == tr) {
      st[v] = val;
      return;
    }
    int tm = (tr + tl) / 2;
    if(pos <= tm) upd(v * 2, tl, tm, pos, val);
    else upd(v * 2 + 1, tm + 1, tr, pos, val);
    st[v] = oper(st[v * 2], st[v * 2 + 1]);
  }
  //indexando desde 0, inclusivo
  void upd(int pos, T val) { upd(1, 0, n - 1, pos, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main(){
  int n, m;
  cin >> n >> m;
  vi h(n);
  vi t(m);
  for(auto &i : h) cin >> i;
  for(auto &i : t) cin >> i;
  STree<int> st(h);
  forn(i, m){
    int val = t[i];
    int l = 0;
    int r = n - 1;
    if(st.st[1] < val) cout << 0 << " ";
    else st.nearestBiggerElem(1, l, r, val);
  }
  return 0;
}
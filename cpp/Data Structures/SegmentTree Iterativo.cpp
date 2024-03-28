const int N = 1e5;  // limit for array size
int t[2 * N];
struct stree{ 
  int n, neutro = 1e9;
  stree(int n): n(n){ forn(i, 2*n) t[i] = neutro; }
  stree(vi a): n(sz(a)){ build(a); }
  inline int op(int a, int b){ return min(a, b); }
  void build(vi& a) { 
    forn(i, n) t[n + i] = a[i];
    rform(i, n-1, 1, 1) t[i] = op(t[i<<1], t[i<<1|1]);
  }
  int query(int l, int r) {  // [l, r]
    int vl = neutro, vr = neutro;
    for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if(l&1) vl = op(vl, t[l++]);
      if(r&1) vr = op(t[--r], vr);
    }
    return op(vl, vr);
  }
  void upd(int p, int val) {  // set val at position p (0 - idx)
    for (t[p += n] = val; p > 1; p >>= 1) t[p>>1] = op(t[p], t[p^1]);
  }
};

//[0, n-1]
vi a = {1 ,2 ,3, 4, 1, 2, 4, 2};
stree st(a);
cout << st.query(0, sz(a) - 1) << ln;


template<typename T>
struct STree {
  int n;
  vector<T> st, lazy;
  T neutro = T(0ll);

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
    return a | b;
  }

  void build(int v, int tl, int tr, vector<T> &a) {
    if(tl == tr) {
      st[v] = 1ll << a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm + 1, tr, a);
    st[v] = oper(st[v * 2], st[v * 2 + 1]);
  }

  void push(int v, int tl, int tr) {
    if (!lazy[v]) return;
    st[v] = 1ll << lazy[v];
    if (tl != tr) {
      lazy[v * 2] = lazy[v * 2 + 1] = lazy[v];
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
    upd(v * 2, tl, tm, l, r, val);
    upd(v * 2 + 1, tm + 1, tr, l, r, val);
    st[v] = oper(st[v * 2], st[v * 2 + 1]);
  }

  T query(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if(tl > r || tr < l) return neutro;
    if (l <= tl && tr <= r) return st[v];
    int tm = (tl + tr) / 2;
    return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
  }

  void upd(int l, int r, T val) {
    upd(1, 0, n - 1, l, r, val);
  }
  T query(int l, int r) {
    return query(1, 0, n - 1, l, r);
  }
};

const int MAXN = 4e5 +5;
vi g[MAXN];
vi tin, tout;
vll aplanado;
int timer = 0;

int n, q;
vi color;
void dfs(int node, int par) {
  tin[node] = timer;
  //se usa el color como el aplanado
  //se puede cambiar segun sea
  aplanado[timer] = color[node];
  timer++;
  for(int next: g[node]) {
    if(next != par) {
      dfs(next, node);
    }
  }
  tout[node] = timer - 1;
}
// Ejemplo de uso
//https://codeforces.com/contest/620/problem/E

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  tin = vi(n + 1);
  tout = vi(n + 1);
  aplanado = vll(n + 1);
  color = vi(n + 1);
  forab(i, 1, n + 1) {
    int x;
    cin >> x;
    color[i] = x;
  }
  int a, b;
  forn(i, n - 1) {
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs(1, 0);
  int oper, v, c;
  STree<ll> st(aplanado);
  while(q--) {
    cin >> oper;
    if(oper == 1) {
      cin >> v >> c;
      // l = timepoEntrada
      // r = tiempoSalida
      // (tin[v], tout[v]) = subArbol del nodo v
      //cambiamos el color del subarbol de v
      st.upd(tin[v], tout[v], c);
    } else {
      cin >> v;
      ll ans = st.query(tin[v], tout[v]);
      //cantidad de colores diferentes en
      //el subarbol de v
      cout << __builtin_popcountll(ans) << ln;
    }
  }
  return 0;
}

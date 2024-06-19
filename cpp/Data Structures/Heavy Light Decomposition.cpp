
const int N = 2e5 + 5;
const int D = 19;
const int S = (1 << D);

int n, q;
ll v[N]; //value of each node
ll st[S]; //segtree
vi g[N]; //graph
int tam[N];//subtree size
int p[N], dep[N];
int id[N];//id of node in the segtree
int tp[N];


ll oper(ll a, ll b) {
  return max(a, b);
}

void update(int idx, ll val) {
  st[idx += n] = val;
  for (idx /= 2; idx; idx /= 2){
    st[idx] = oper(st[2 * idx], st[2 * idx + 1]);
  }
}

ll query(int lo, int hi) {
  ll ra = 0, rb = 0;
  for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
    if (lo & 1) ra = oper(ra, st[lo++]);
    if (hi & 1) rb = oper(rb, st[--hi]);
  }
  return oper(ra, rb);
}

int dfs_sz(int cur, int par) {
  tam[cur] = 1;
  p[cur] = par;
  for (int chi : g[cur]) {
    if (chi == par) continue;
    dep[chi] = dep[cur] + 1;
    p[chi] = cur;
    tam[cur] += dfs_sz(chi, cur);
  }
  return tam[cur];
}

int ct = 1;

void dfs_hld(int cur, int par, int top) {
  id[cur] = ct++;
  tp[cur] = top;
  update(id[cur], v[cur]);
  int h_chi = -1, h_sz = -1;
  for (int chi : g[cur]) {
    if (chi == par) continue;
    if (tam[chi] > h_sz) {
      h_sz = tam[chi];
      h_chi = chi;
    }
  }
  if (h_chi == -1) return;
  dfs_hld(h_chi, cur, top);
  for (int chi : g[cur]) {
    if (chi == par || chi == h_chi) continue;
    dfs_hld(chi, cur, chi);
  }
}

ll path(int x, int y) {
  ll ret = 0;
  while (tp[x] != tp[y]) {
    if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
    ret = oper(ret, query(id[tp[x]], id[x]));
    x = p[tp[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  ret = oper(ret, query(id[x], id[y]));
  return ret;
}

int main() {
  cin >> n >> q;
  forab(i, 1,n + 1) cin >> v[i];
  forn(i, n - 1) {
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs_sz(1, 1);
  dfs_hld(1, 1, 1);
  int op;
  while (q--) {
    cin >> op;
    if(op == 1){
      int s, x;
      cin >> s >> x;
      v[s] = x;
      update(id[s], x);
    }else{
      int a, b;
      cin >> a >> b;
      ll res = path(a, b);
      cout << res << " ";
    }
  }
  cout << ln;
  return 0;
}
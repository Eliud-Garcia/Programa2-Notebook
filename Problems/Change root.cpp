// cada nodo se elige como raiz y dice
// cuantos nodos estan pintados en su subArbol
// https://codeforces.com/gym/102348/problem/B

const int MAXN = 2e5 + 5;
vi g[MAXN];
vll sum;
vb colored;
vi ans;

int n, k;
void dfs(int node, int p) {
  if(colored[node])sum[node]++;
  for(int next: g[node]) {
    if(next == p) continue;
    dfs(next, node);
    sum[node]+=sum[next];
  }
}
void change_root(int root, int p) {
  bool ok = !colored[root];
  for (int child : g[root]) {
    ok &= (sum[child] > 0);
  }
  if (ok) ans.pb(root);
  for (int next : g[root]) {
    if (next == p)continue;
    ll prevRoot = sum[root];
    ll prevNext = sum[next];
    sum[root] -= sum[next];
    sum[next] = prevRoot;
    change_root(next, root);
    sum[root] = prevRoot;
    sum[next] = prevNext;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  sum = vll(n + 1);
  colored = vb(n + 1, 0);
  forn(i, k) {
    int x;
    cin >> x;
    colored[x] = 1;
  }
  int a, b;
  forn(i, n - 1) {
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs(1, 1);
  change_root(1, 1);
  cout << ans.size() << ln;
  sort(all(ans));
  for(int u: ans) {
    cout << u << " ";
  }
  cout << ln;
  return 0;
}


int main() {
  cin >> n >> m;
  int a, b;
  vi grado(n + 1, 0);
  forn(i, m){
    cin >> a >> b;
    g[a].pb(b);
    grado[b]++;
  }
  vi topo = topo_sort(grado);
  int source = 1;
  int dest = n;
  //cuidado con overflow
  int dp[n] = { 0 };
  dp[dest] = 1;
  // traverse in reverse order
  rforn (i, sz(topo)) { // O(n + m)
    forn (j, sz(g[topo[i]])) {
      dp[topo[i]] += dp[g[topo[i]][j]];
    }
  }
  //number of paths from source
  //to dest
  cout << dp[source] << ln;
  return 0;
}
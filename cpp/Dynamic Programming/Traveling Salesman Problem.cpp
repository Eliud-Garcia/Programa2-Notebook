
//shortest route
//it is a closed cycle where it
//ends at the same point it starts

// it visits each node exactly once
const int oo = 1e9;
int n, m;
const int N = 16;
vector<vi> g(N, vi(N, oo)); // directed graph
int dp[1 << N][N];

int go(int mask, int u) {
  if(mask == ((1 << n) - 1)) {
    return g[u][0] != oo ? g[u][0] : oo;
  }
  if(dp[mask][u] != - 1) return dp[mask][u];

  int ans = oo;
  forn(v, n) {
    if((mask & (1 << v)) == 0) {
      int aux = go(mask | (1 << v), v) + g[u][v];
      ans = min(ans, aux);
    }
  }
  return dp[mask][u] = ans;
}

int main() {
  cin >> n >> m;
  int a, b, w;
  forn(i, m) {
    cin >> a >> b >> w;
    g[a][b] = w;
  }
  memset(dp, -1, sizeof dp);
  int ans = go(1, 0); // mask, node
  cout << (ans == oo ? -1: ans) << ln;
  return 0;
}
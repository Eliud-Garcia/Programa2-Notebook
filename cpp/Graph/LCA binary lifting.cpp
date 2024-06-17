#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define forn(i, n) for(int i = 0; i < n; i++)
#define forab(i, a, b) for (int i = a; i < b; i++)
#define pb push_back
#define sz(x) int(x.size())
#define rforn(i, n) for (int i = n-1; i >= 0; --i)
#define form(i, n, m, x) for (int i = n; i < m; i += x)
#define rform(i, n, m, x) for (int i = n; i >= m; i -= x)

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...)
#endif

typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;

int n, q, LOG;
const int MAXN = 5e5 + 5;
vi g[MAXN];
vi deep(MAXN);
vector<vi> up;
int cnt = 1;
void dfs(int u, int p) {
  for(int v : g[u]) {
    if(v!=p) {
      deep[v] = deep[u] + 1;
      up[0][v] = u;
      dfs(v, u);
    }
  }
}
void build(int n, int root) {
  dfs(root, root);
  forab(i, 1, LOG + 1) { //logs
    forab (u, 1, n) {//nodo
      if (up[i - 1][u] != -1) {
        up[i][u] = up[i - 1][up[i - 1][u]];
      }
    }
  }
}
int lca(int u, int v) {
  if (deep[u] > deep[v]) {
    int tmp = u;
    u = v;
    v = tmp;
  }
  int diff = deep[v] - deep[u];
  rform (i, LOG - 1, 0, 1) {
    if((diff & (1 << i))) {
      v = up[i][v];
    }
  }
  if (u == v) return u;
  rform (i, LOG - 1, 0, 1) {
    if (up[i][v] != up[i][u]) {
      u = up[i][u];
      v = up[i][v];
    }
  }
  return up[0][u];
}

int main() {
  cin >> n;
  LOG = int(log2(n + 1) + 1);
  up = vector<vi>(LOG + 1, vi(n + 1));
  int a, b, c;
  forn (i, n - 1) {
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  int root = 1;
  build(n + 1, root);
  cin >> q;
  while (q--) {
    cin >> a >> b >> c;
    int ancestor = lca(a, b);
    int disAB = deep[a] + deep[b] - (2 * deep[ancestor]);
    int disA_lca = deep[a] - deep[ancestor];
    if (disAB <= c) {
      cout << b << ln;
    } else {
      if (disA_lca >= c) {
        //nos acercamos dando brincos
        //en potencias de 2
        rform (k, LOG, 0, 1) {
          if (((c >> k) & 1)) {
            a = up[k][a];
          }
        }
        cout << a << ln;
      } else {
        int df = disAB - c;
        rform (k, LOG, 0, 1) {
          if (((df >> k) & 1)) {
            b = up[k][b];
          }
        }
        cout << b << ln;
      }
    }
  }
  return 0;
}

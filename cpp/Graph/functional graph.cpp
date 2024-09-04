
//choose min cost in cycle
const int MAXN = 2e5 + 5;
int n;
vi g[MAXN];
vb vis(MAXN, 0);
vb in_cycle(MAXN, 0);
vi id(MAXN, -1);
int cost[MAXN];
int mo[MAXN];

int mn = 2e9;
int tag = 1;

void dfs(int u, stack<int> &st) {
  vis[u] = 1;
  id[u] = tag;
  st.push(u);
  for(int v: g[u]) {
    if(!vis[v]) {
      dfs(v, st);
    } else {
      if(id[u] == id[v]) {
        while(sz(st)) {
          int node = st.top();
          st.pop();
          mn = min(mn, cost[node]);
          //cout << node << ln;
          in_cycle[node] = 1;
          if(node == v) {
            break;
          }
        }
      } else {
        if(id[u] != id[v] && !in_cycle[u] && in_cycle[v]) {
          id[u] = id[v];
          mn = 0;
        } else if(id[u] != id[v] && !in_cycle[u] && !in_cycle[v]) {
          id[u] = id[v];
          mn = 0;
        }
      }
    }
  }
  //if id is incorret
  //iterate over childs
  //and propagate ids
}

int main() {
  cin >> n;
  forab(i, 1, n + 1) {
    cin >> cost[i];
  }
  forab(i, 1, n + 1) {
    cin >> mo[i];
    g[i].pb(mo[i]);
  }
  int ans = 0;
  forab(i, 1, n + 1) {
    if(!vis[i]) {
      mn = 2e9;
      stack<int> st;
      dfs(i, st);
      tag++;
      ans += mn;
    }
  }
  cout << ans << ln;
  return 0;
}

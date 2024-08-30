
//directed graph
int n, m;
const int MAXN = 1e5 + 5;
vi g[MAXN];
vi par(MAXN, -1);
vi color(MAXN, 0);
int inicio = -1, fin = -1;
vi cycle;

bool dfs(int u){
  color[u] = 1;
  for(int v: g[u]){
    if(color[v] == 0){
      par[v] = u;
      if(dfs(v)) return 1;
    }else if(color[v] == 1){
      if(inicio != -1 && fin != -1) return 1;
      inicio = u;
      fin = v;
      vi aux;
      int cur = u;
      aux.pb(cur);
      while(cur != v){
        cur = par[cur];
        aux.pb(cur);
      }
      aux.pb(u);
      if(sz(aux) >= 2){
        reverse(all(aux));
        cycle = aux;
      }
      return 1;
    }
  }
  color[u] = 2;
  return 0;
}

int main() {
  cin >> n >> m;
  int a, b;
  forn(i, m){
    cin >> a >> b;
    g[a].pb(b);
  }
  forab(i, 1, n + 1){
    if(color[i] == 0 && dfs(i))break;
    if(sz(cycle) > 0) break;
  }
  if(sz(cycle) == 0){
    puts("IMPOSSIBLE");
  }else{
    printf("%d\n", sz(cycle));
    for(int i : cycle){
      printf("%d ", i);
    }
    puts("");
  }
  return 0;
}

//undirected graph
const int MAXN = 1e5 + 5;
vi g[MAXN];
vb vis;
vi parent;
int n, m;
int cycle_start = -1;
int cycle_end = -1;

bool dfs(int node, int par) {
  vis[node] = 1;
  parent[node] = par;
  for(int next: g[node]) {
    if(next == par) continue;
    if(vis[next]) {
      cycle_start = next;
      cycle_end = node;
      return 1;
    }
    if(!vis[next] && dfs(next, node)) return 1;
  }
  return false;
}
int main() {
  cin >> n >> m;
  vis = vb(n + 1, 0);
  parent = vi(n + 1);
  forn(i, m) {
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  forab(i, 1, n + 1) {
    if(!vis[i] && dfs(i, -1)) break;
  }
  if(cycle_start == -1) //no hay ciclo
    else //hay ciclo
      //se puede recorrer el ciclo
      //usando el array de padres
      return 0;
}

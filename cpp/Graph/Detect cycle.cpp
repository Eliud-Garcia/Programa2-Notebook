
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
const int MAXN = 2e5 + 5;
int color[MAXN];
int mark[MAXN];
int par[MAXN];
vi g[MAXN];

void dfs(int u, int p, int &cy){
    if(color[u] == 2){
        return;
    }
    if(color[u] == 1){
        cy++;
        int cur = p;
        mark[cur] = cy;
        while(cur != u){
            cur = par[cur];
            mark[cur] = cy;
        }
        return;
    }
    par[u] = p;
    color[u] = 1;
    for(int v: g[u]){
        if(v == par[u]) continue;
        dfs(v, u, cy);
    }
    color[u] = 2;
}

/*
    forab(i, 1, n + 1){
        color[i] = 0;
        par[i] = i;
        mark[i] = -1;
    }
    int cycles = 0;
    dfs(1, 1, cycles);

    forab(i, 1, n + 1){
        if(mark[i] != -1){
            found = true;
        }
    }
*/

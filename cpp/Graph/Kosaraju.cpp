
const int MAXN = 1e5 + 5;
int n, m;
vi g[MAXN];
vi rg[MAXN];
vb vis(MAXN);
vi id(MAXN);
int tagSCC;
vector<vi> SCC;
vi curComp;

void dfs1(int u, stack<int> &st){
  vis[u] = 1;
  for(int v: g[u]){
    if(!vis[v]) dfs1(v, st);
  }
  st.push(u);
}
void dfs2(int u){
  vis[u] = 1;
  id[u] = tagSCC;
  curComp.pb(u);
  //u esta en la SCC id[u]
  for(int v: rg[u]){
    if(!vis[v])dfs2(v);
  }
}

int main(){
  cin >> n >> m;
  int a, b;
  forn(i, m){
    cin >> a >> b;
    g[a].pb(b);
    rg[b].pb(a);
  }
  stack<int> st;
  forab(i, 1, n + 1){
    if(!vis[i])dfs1(i, st);
  }
  vis = vb(n + 1, 0);
  while(!st.empty()){
    int u = st.top(); st.pop();
    if(vis[u]) continue;
    tagSCC++;
    curComp.clear();
    dfs2(u);
    SCC.pb(curComp);
  }
  //build DAG
  const int MAXDAG = tagSCC + 1;
  vi dag[MAXDAG];
  forab(u, 1, n + 1){
    for(int v: g[u]){
      if(id[u] == id[v]) continue;
      dag[id[u]].pb(id[v]);
    }
  }
  //print SCC
  int cp = 1;
  for(vi i: SCC){
    printf("SCC #%d: ", cp++);
    for(int u: i){
      printf("%d ", u);
    }
    printf("\n");
  }
  return 0;
}
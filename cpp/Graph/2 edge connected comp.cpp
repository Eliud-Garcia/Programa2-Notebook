
typedef pair<int, int> pii;
struct edge {
  int u, v, id, yes;
  edge() {};
  edge(int u, int v, int id, int yes) :
    u(u), v(v), id(id), yes(yes) {};
};

const int N = 3e5 + 5;
const int M = 3e5 + 5;
 
bool vis[N], isBridge[M];
int tin[N], low[N], comp[N];
int found[N];

vector<pii> g[N];
//2-edge-connected component tree(Bridge Tree)
vector<pii> tree[N];
vector<edge> edges;
 
int n, m, timer, compid;

//encontrar puentes
void dfs(int v, int p) {
  tin[v] = low[v] = ++timer;
  vis[v] = true;
  for(auto &[to, id]: g[v]) {
    if(to == p) continue;
    if(vis[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if(low[to] > tin[v]) {
        isBridge[id] = true;
      }
    }
  }
}

//asignar comp a nodos
void dfs1(int v) {
  vis[v] = 1;
  comp[v] = compid;
  for(auto &[to, id]: g[v]) {
    //omitir los bridges
    if(isBridge[id])continue;
    if(edges[id].yes) {
      found[compid] = true;
    }
    if(!vis[to]) dfs1(to);
  }
}

bool done = false;
//existe un artefect desde u hasta v
//en el bridge tree
void dfs2(int u, int v, int ans) {
  vis[u] = true;
  ans |= found[u];
  if(u == v) {
    done = ans;
  }
  for(auto &[to, id]: tree[u]) {
    if(!vis[to])
      dfs2(to, v, ans | edges[id].yes);
  }
}

int main(){
  cin >> n >> m;
  edges = vector<edge>(m + 1);
  int u, v, z;
  forab(id, 1, m + 1){
    cin >> u >> v >> z;
    g[u].pb({v, id});
    g[v].pb({u, id});
    edges[id] = {u, v, id, z};
  }
  int a, b;
  cin >> a >> b;

  //armar edge tree
  timer = 0, compid = 0;
  dfs(1, -1);
  forab(i, 1, n + 1) vis[i] = 0;
  forab(i, 1, n + 1){
    if(!vis[i]){
      dfs1(i);
      ++compid;
    }
  }
  forab(id, 1, m + 1){
    if(isBridge[id]){
      int u = edges[id].u;
      int v = edges[id].v;
      tree[comp[u]].pb({comp[v], id});
      tree[comp[v]].pb({comp[u], id});
    }
  }

  forab(i, 1, compid+1) vis[i] = 0;
  dfs2(comp[a], comp[b], 0);
  cout << (done? "YES" : "NO") <<ln;
  return 0;
}
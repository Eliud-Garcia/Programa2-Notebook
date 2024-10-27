
struct edge{
  int u;
  ll w;
  bool operator < (const edge &x) const {
    return x.w < w;
  }
};

int n, m;
const int MAXN = 2e5 + 5;
const ll oo = (1LL << 62);
vector<edge> g[MAXN];
vi par(MAXN);

vll dijkstra(int s) {
  priority_queue<edge> pq;
  vll dis(n + 1, oo);
  pq.push(edge{s, 0});
  dis[s] = 0;
  par[s] = -1;
  while (sz(pq)) {
    auto [u, cur_dis] = pq.top();
    pq.pop();
    ll min_dis = dis[u];
    if(cur_dis != min_dis) continue;
    for (auto [v, w] : g[u]) {
      if (dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        par[v] = u;
        pq.push(edge{v, dis[v]});
      }
    }
  }
  return dis;
}

int main() {
  cin >> n >> m;
  forn(i, m){
    int a, b, w;
    cin >> a >> b >> w;
    g[a].pb({b, w});
    g[b].pb({a, w});
  }
  vll dis = dijkstra(1);
  if(dis[n] != oo){
    vi path;
    for (int i = n; i != -1; i = par[i]) {
      path.pb(i);
    }
    rforn (i, sz(path)) {
      cout << path[i] << " ";
    }
    cout << ln;
  } else {
    cout << "-1" << ln;
  }
  return 0;
}

//validar si una arista
//esta en el camino mas corto
//desde (a, b)
vll da = dijkstra(1);
ll minDis = da[n];
vll db = dijkstra(n);
vector<ll> shortes_path;
for (auto [u, v, w] : edges) {
  if(da[u] + w + db[v] == minDis) {
      //edge is on shortest path
      //do something
  }
  if(da[v] + w + db[u] == minDis) {
      //edge is on shortest path
      //do something
  }
}

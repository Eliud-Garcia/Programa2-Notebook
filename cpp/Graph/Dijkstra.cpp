const ll oo = LLONG_MAX;
struct edge {
  int v;
  ll w;
  edge(int node, ll weight): v(node), w(weight){}
  bool operator<(const edge& x) const{
    return x.w < w;
  }
};
const int MAXN = 2e5 + 5;
vector<edge> g[MAXN];
vi par;
vb vis;
int n, m;

vll dijkstra(int s){
  priority_queue<edge> pq;
	vll dis(n + 5, oo);
	pq.push(edge(s, 0));
	dis[s] = 0;
	par[s] = -1;
	while (!pq.empty()) {
		edge x = pq.top();
		pq.pop();
		int u = x.v;
		vis[u] = true;
		for (edge next : g[u]) {
			int v = next.v;
			ll  w = next.w;
			if (!vis[v] && dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				par[v] = u;
				pq.push(edge(v, dis[v]));
			}
		}
	}
	return dis;
}

int main(){
	cin >> n >> m;
	par = vi(n + 5, -1);
	vis = vb(n + 5, 0);
	int a, b;
	ll w;
	forn (i, m) {
		cin >> a >> b >> w;
		g[a].pb(edge(b, w));
		g[b].pb(edge(a, w));
	}
	dijkstra(1);
	if (vis[n]) {
		vi path;
		for (b = n; b != -1; b = par[b]) {
			path.pb(b);
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
vll da = dijkstra(a);
ll minDis = da[b];
vll db = dijkstra(b);
for (edge e : aristas) {
  //edge is on shortest path
  if(disSource[e.u] + e.w + disDest[e.v] == minDis){
    continue;
  }
  //edge is on shortest path
  if(disSource[e.v] + e.w + disDest[e.u] == minDis){
    continue;
  }
}
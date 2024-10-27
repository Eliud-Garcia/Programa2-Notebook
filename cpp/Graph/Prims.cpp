//MST
//O(E log N )
struct edge {
   int v;
   ll w;
   int idx;

   bool operator < (const edge &x) const {
      return w > x.w; //min
   }
};

int n, m;
const int MAXN = 3e5 + 5;
vector<edge> g[MAXN];
vector<array<ll, 4>> edges;

vector<vector<edge>> prims(int src){
   vector<vector<edge>> tree(n + 1);
   priority_queue<edge> pq;

   vb vis(n + 1, 0);
   vis[src] = 1;

   for (auto &[v, w, id] : g[src]) {
      if (!vis[v]){
         pq.push(edge{v, w, id});
      }
   }

   ll mst = 0;
   while (sz(pq)) {
      auto [u, w, id] = pq.top();
      pq.pop();

      if (!vis[u]) {
         vis[u] = true;
         dbg(id + 1);
         mst += w;
         //arista de mst
         auto [uu, vv, ww, _] = edges[id];
         tree[uu].pb({uu, ww});
         tree[vv].pb({vv, ww});

         for (auto &[v, w, idx] : g[u]) {
            if (!vis[v]) {
               pq.push(edge{v, w, idx});
            }
         }
      }
   }
   return tree;
}

int main() {
   cin >> n >> m;
   edges.resize(m);
   forn(i, m){
      int a, b, w;
      cin >> a >> b >> w;
      g[a].pb({b, w, i});
      g[b].pb({a, w, i});
      edges[i] = {a, b, w, i};
   }

   vector<vector<edge>> tree = prims(1);
   return 0;
}
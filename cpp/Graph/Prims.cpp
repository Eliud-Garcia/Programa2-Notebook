//MST
//O(E log N )
struct edge {
   int v;
   ll w;
   int idx;

   bool operator < (const edge &x) const {
      return w > x.w;
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

   for (edge &i: g[src]) {
      if (!vis[i.v]){
         pq.push(i);
      }
   }

   ll mst = 0;
   while (sz(pq)) {
      edge u = pq.top();
      pq.pop();

      if (!vis[u.v]) {
         //arista del MST
         auto [uu, vv, ww, id] = edges[u.idx];
         tree[uu].pb(edge{vv, ww, id});
         tree[vv].pb(edge{uu, ww, id});
         mst += ww;
         vis[u.v] = 1;

         for (edge &v : g[u.v]) {
            if (!vis[v.v]) {
               pq.push(v);
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
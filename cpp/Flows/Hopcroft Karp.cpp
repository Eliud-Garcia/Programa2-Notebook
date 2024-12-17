
using ii = pair<int, int>;

struct mbm { // O(E * sqrt(V))
  int nl, nr, flow = 0;
  vector<vector<int>> g;
  vector<int> dist, mfl, mfr;

  mbm(int nl, int nr):
    nl(nl), nr(nr), g(nl), mfl(nl, -1),
    mfr(nr, -1), dist(nl) {}

  void add(int u, int v) { g[u].push_back(v); }

  void bfs() {
    queue<int> q;
    forn (u, nl)
      if (!~mfl[u]) q.push(u), dist[u] = 0;
      else dist[u] = -1;
    while (sz(q)) {
      int u = q.front();
      q.pop();
      for (auto &v : g[u])
        if (~mfr[v] && !~dist[mfr[v]]) {
          dist[mfr[v]] = dist[u] + 1;
          q.push(mfr[v]);
        }
    }
  }

  bool dfs(int u) {
    for (auto &v : g[u])
      if (!~mfr[v]) {
        mfl[u] = v, mfr[v] = u;
        return true;
      }
    for (auto &v : g[u])
      if (dist[mfr[v]] == dist[u] + 1 && dfs(mfr[v])) {
        mfl[u] = v, mfr[v] = u;
        return true;
      }
    return false;
  }

  int get_matching() {
    while (true) {
      bfs();
      int agt = 0;
      forn (u, nl)
        if (!~mfl[u]) agt += dfs(u);
      if (!agt) break;
      flow += agt;
    }
    return flow;
  }

  pair<vector<int>, vector<int>> MVC() {
    vector<int> L, R;
    forn (u, nl)
      if (!~dist[u]) L.push_back(u);
      else if (~mfl[u]) R.push_back(mfl[u]);
    return {L, R};
  }

  vector<ii> get_edges() {
    vector<ii> ans;
    forn (u, nl)
      if (mfl[u] != -1)
        ans.pb({u, mfl[u]});
    return ans;
  }
};

/*Maximum Independent Set: 
Subset of nodes 
with the following propriety: 
For any two nodes u, v 
are not adjacent 
(There is no direct edge between nodes  u and  v).
*/

/*Minimum Vertex Cover: 
A vertex cover is a subset of the nodes 
that together touch all the edges.
*/

// Min Vertex Cover: vertices de L con level[v]==-1 y vertices de R con level[v]>0
// Max Independent Set: vertices NO tomados por el Min Vertex Cover

//Max Independet Set = |V| - size of the MCBM
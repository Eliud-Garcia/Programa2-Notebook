struct UnionFind {
  vi p, c_sz;
  vi maxi, mini;

  UnionFind(int n) {
    p = vi(n);
    c_sz = vi(n);
    maxi = vi(n);
    mini = vi(n);
    forn(i, n) {
      p[i] = i, c_sz[i] = 1;
      maxi[i] = i;
      mini[i] = i;
    }
  }
  // Path compression optimization
  int find(int a) {
    return p[a] = (p[a] == a) ? a : find(p[a]);
  }
  // Union by size
  void unite(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (a == b)return;
    if(c_sz[a] < c_sz[b]) swap(a, b);
    p[b] = a;
    c_sz[a] += c_sz[b];
    mini[a] = min(mini[a], mini[b]);
    maxi[a] = max(maxi[a], maxi[b]);
  }

  bool isSame(int a, int b) {
    return find(a) == find(b);
  }
  int comp_sz(int u){
    return c_sz[find(u)];
  }
};

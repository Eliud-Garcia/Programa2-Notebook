struct UnionFind {
  vi parent;
  vi comp_sz;
  vi maxi;
  vi mini;

  UnionFind(int n) {
    n++;
    parent = vi(n);
    comp_sz = vi(n);
    maxi = vi(n);
    mini = vi(n);
    forn(i, n) {
      parent[i] = i;
      comp_sz[i] = 1;
      maxi[i] = i;
      mini[i] = i;
    }
  }
  // Path compression optimization
  int find(int a) {
    return parent[a] = (parent[a] == a) ? a : find(parent[a]);
  }
  // Union by size
  void unite(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (a == b)return;
    if(comp_sz[a] < comp_sz[b]) swap(a, b);
    parent[b] = a;
    mini[a] = min(mini[a], mini[b]);
    maxi[a] = max(maxi[a], maxi[b]);
    comp_sz[a] += comp_sz[b];
  }

  bool isSame(int a, int b) {
    return find(a) == find(b);
  }
};

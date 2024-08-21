
//for each node, the longest distance to any other
//edges with cost

ll down[MAXN], up[MAXN];
vector<pair<int, ll>> tree[MAXN];
void dfs_down(int u, int parent) {
  down[u] = 0;
  for (auto [v, w] : tree[u]) {
    if (v != parent) {
      dfs_down(v, u);
      down[u] = max(down[u], down[v] + w);
    }
  }
}

void dfs_up(int u, int parent) {
  int max1 = -1, max2 = -1; // Las dos mayores distancias hacia abajo desde u
  // Encuentra las dos mayores distancias hacia abajo
  for (auto [v, w] : tree[u]) {
    if (v != parent) {
      int total_dist = down[v] + w;
      if (total_dist > max1) {
        max2 = max1;
        max1 = total_dist;
      } else if (total_dist > max2) {
        max2 = total_dist;
      }
    }
  }

  //up[v] para cada hijo v
  for (auto [v, w] : tree[u]) {
    if (v != parent) {
      if (down[v] + w == max1) {
        up[v] = max(up[u] + w, max2 + w);
      } else {
        up[v] = max(up[u] + w, max1 + w);
      }
      dfs_up(v, u);
    }
  }
}
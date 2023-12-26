#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define forn(i, n) for (int i = 0; i < n; i++)
#define forab(i, a, b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

// Lowest Common Ancestor
// Se usa el Euler tour para encontrar un nodo que
// está entre u y v que tiene la altura mas baja
struct LCA {
    vi height, euler, first, st;//SegmentTree
    vector<vi> table; // Sparse Table
    vector<bool> vis;
    int n;
    bool SegTree;

    // LCA with segment tree -> option = 1
    // LCA with Sparse Table -> option = 2
    LCA(vector<vi>& g, int root, int option){
        n = g.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        vis.assign(n, false);
        dfs(g, root, 0);
        if (option == 1) {
            SegTree = true;
            int m = euler.size();
            st.resize(m * 4);
            build(1, 0, m - 1);
        } else if(option == 2) {
            SegTree = false;
            build();
        }
    }

    void dfs(vector<vi>& g, int node, int h){
        vis[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.pb(node);
        for (auto to : g[node]) {
            if (!vis[to]) {
                dfs(g, to, h + 1);
                euler.pb(node);
            }
        }
    }

    void build(int node, int b, int e){
        if (b == e) {
            st[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = st[node << 1], r = st[node << 1 | 1];
            st[node] = (height[l] < height[r]) ? l : r;
        }
    }

    int query(int node, int b, int e, int L, int R){
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return st[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1)
            return right;
        if (right == -1)
            return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v){
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        if (SegTree) {
            return query(1, 0, euler.size() - 1, left, right);
        } else {
            return query(left, right);
        }
    }

    void build(){
        int N = euler.size();
        int K = int(log2(N)) + 1;
        table.assign(N + 1, vi(K));
        forn(i, N){
            table[i][0] = euler[i];
        }
        forn(j, K - 1){
            for (int i = 0; i + (1 << (j + 1)) <= N; ++i) {
                int a = table[i][j];
                int b = table[i + (1 << j)][j];
                table[i][j + 1] = height[a] < height[b] ? a : b;
            }
        }
    }

    int query(int l, int r){
        int k = 31 - __builtin_clz(r - l + 1);
        int a = table[l][k];
        int b = table[r - (1 << k) + 1][k];
        return height[a] < height[b] ? a : b;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<vi> g(n + 1, vi());
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    LCA lca(g, 1, 2);
    while (q--) {
        cin >> a >> b;
        int LCA = lca.lca(a, b);
        cout << lca.height[a] + lca.height[b] - (2 * lca.height[LCA]) << ln;
    }

    return 0;
}
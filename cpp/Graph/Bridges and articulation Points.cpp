#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define forn(i, n) for (int i = 0; i < n; i++)
#define forab(i, a, b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef pair<int, int> ii;

// Tarjan's Algorithm
// Finding bridges in a graph in O(N + M)
// Undirected graph.

const int MAXN = (int) 1e5 + 5; // cant nodos
vi g[MAXN];
vi tin, low;
int timer = 0;
vector<ii> bridges;
vb is_articulation, vis;
int n, m;

void dfs(int v, int p = -1){
    vis[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int u : g[v]) {
        if (u == p) continue;
        if (vis[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] >= tin[v] && p != -1)
                is_articulation[v] = true;
            ++children;
            if (low[u] > tin[v])
                bridges.pb({ v, u });
        }
    }
    if (p == -1 && children > 1)
        is_articulation[v] = true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    tin = vi(n + 1, -1);
    low = vi(n + 1, -1);
    vis = vb(n + 1, 0);
    is_articulation = vb(n + 1, 0);

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    // find bridges and articulation points
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }

    // print articulation points
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) {
            cout << i << ln;
        }
    }

    // print bridges
    for (auto i : bridges) {
        cout << i.first << "-" << i.second << ln;
    }
    return 0;
}
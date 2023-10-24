


const long long INF = LLONG_MAX;

struct edge {
    int v;
    long long w;

    edge(int node, long long weight)
        : v(node)
        , w(weight)
    {
    }
    bool operator<(const edge& x) const
    {
        return x.w < w;
    }
};

vector<vector<edge>> g;
vector<long long> dis;
vector<int> par;
vector<bool> vis;

bool dijkstra(int s, int t)
{
    priority_queue<edge> pq;

    pq.push(edge(s, 0));
    dis[s] = 0;
    par[s] = -1;

    while (!pq.empty()) {
        edge x = pq.top();
        pq.pop();
        int u = x.v;

        if (u == t) {
            return true;
        }

        vis[u] = true;

        for (edge next : g[u]) {
            int v = next.v;
            long long w = next.w;

            if (!vis[v] && dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push(edge(v, dis[v]));
                par[v] = u;
            }
        }
    }

    return false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    g.resize(n + 3);
    dis.assign(n + 3, INF);
    par.assign(n + 3, -1);
    vis.assign(n + 3, false);

    int a, b;
    long long w;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        g[a].push_back(edge(b, w));
        g[b].push_back(edge(a, w));
    }

    if (dijkstra(1, n)) {
        vector<int> path;
        for (b = n; b != -1; b = par[b]) {
            path.push_back(b);
        }

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << " ";
        }
        cout << ln;
    } else {
        cout << "-1" << ln;
    }

    return 0;
}
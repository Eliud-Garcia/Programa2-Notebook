
int n, m;
const int MAXN = 2505;
const int MAXM = 5005;
const ll oo = 1e18 + 5;

array<ll, 3> edges[MAXM];
int par[MAXN];
ll dis[MAXN];

int main() {
    cin >> n >> m;
    forn(i, m) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, -w};
    }

    //negative cycle
    vb change(n + 1, 0);
    forab(i, 1, n + 1) dis[i] = oo;
    dis[1] = 0;
    int x;
    forn(i, n) {
        x = -1;
        for(auto [a, b, w]: edges) {
            if(dis[a] < oo) {
                if(dis[b] > dis[a] + w) {
                    if(i == n - 1) change[b] = 1;
                    dis[b] = max(-oo, dis[a] + w);
                    par[b] = a;
                    x = b;
                }
            }
        }
    }
    bool cycle = (x != -1);
    bool valid_cycle = 0;

    if(cycle) {
        /*
        int y = x;
        forn(i, n) y = par[y];
        vi path;
        for(int cur = y;; cur = par[cur]){
          path.pb(cur);
          if(cur == y && sz(path) > 1) break;
        }
        */
        dfs1(1);//normal graph
        dfs2(n);//reverse graph

        forab(i, 1, n + 1) {
            if(change[i]) {
                if(vis1[i] && vis1[n]) {
                    if(vis2[i] && vis2[1]) {
                        valid_cycle = 1;
                        break;
                    }
                }
            }
        }
    }

    if(valid_cycle) {
        puts("-1");
    } else {
        printf("%lld\n", -dis[n]);
    }
    return 0;
}

//shortest path
forab(i, 1, n + 1) dis[i] = oo;
int source = 1;
int dest = n;
par[source] = -1;
d[source] = 0;
forn (i, n - 1) {
    for (auto [a, b, w] : edges) {
        if (dis[a] < oo) {
            dis[b] = min(dis[b], dis[a] + w);
            par[b] = a;
        }
    }
}
if (dis[dest] == oo) {
    //no path
} else {
    vi path;
    for (int cur = dest; cur != -1; cur = par[cur])
        path.pb(cur);
    reverse(all(path));
}

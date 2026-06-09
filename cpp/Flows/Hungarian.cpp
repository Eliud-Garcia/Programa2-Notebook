
//tomado de: https://github.com/ShahjalalShohag/code-library/
const int N = 509;
/* Complexity: O(n^3) but optimized
It finds minimum cost maximum matching.
For finding maximum cost maximum matching
add -cost and return -matching()
1-indexed */
struct Hungarian {
    ll c[N][N], fx[N], fy[N], d[N];
    int l[N], r[N], arg[N], trace[N];
    queue<int> q;
    int start, finish, n;
    const ll inf = 1e18;
    Hungarian() {
    }
    Hungarian(int n1, int n2) : n(max(n1, n2)) {
        for (int i = 1; i <= n; ++i) {
            fy[i] = l[i] = r[i] = 0;
            for (int j = 1; j <= n; ++j)
                c[i][j] = inf;  // make it 0 for maximum cost matching (not
                                // necessarily with max count of matching)
        }
    }
    void add_edge(int u, int v, ll cost) {
        c[u][v] = min(c[u][v], cost);
    }
    inline ll getC(int u, int v) {
        return c[u][v] - fx[u] - fy[v];
    }
    void initBFS() {
        while (!q.empty()) q.pop();
        q.push(start);
        for (int i = 0; i <= n; ++i) trace[i] = 0;
        for (int v = 1; v <= n; ++v) {
            d[v] = getC(start, v);
            arg[v] = start;
        }
        finish = 0;
    }
    void findAugPath() {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 1; v <= n; ++v)
                if (!trace[v]) {
                    ll w = getC(u, v);
                    if (!w) {
                        trace[v] = u;
                        if (!r[v]) {
                            finish = v;
                            return;
                        }
                        q.push(r[v]);
                    }
                    if (d[v] > w) {
                        d[v] = w;
                        arg[v] = u;
                    }
                }
        }
    }
    void subX_addY() {
        ll delta = inf;
        for (int v = 1; v <= n; ++v)
            if (trace[v] == 0 && d[v] < delta) {
                delta = d[v];
            }
        // Rotate
        fx[start] += delta;
        for (int v = 1; v <= n; ++v)
            if (trace[v]) {
                int u = r[v];
                fy[v] -= delta;
                fx[u] += delta;
            } else
                d[v] -= delta;
        for (int v = 1; v <= n; ++v)
            if (!trace[v] && !d[v]) {
                trace[v] = arg[v];
                if (!r[v]) {
                    finish = v;
                    return;
                }
                q.push(r[v]);
            }
    }
    void Enlarge() {
        do {
            int u = trace[finish];
            int nxt = l[u];
            l[u] = finish;
            r[finish] = u;
            finish = nxt;
        } while (finish);
    }
    ll maximum_matching() {
        for (int u = 1; u <= n; ++u) {
            fx[u] = c[u][1];
            for (int v = 1; v <= n; ++v) {
                fx[u] = min(fx[u], c[u][v]);
            }
        }
        for (int v = 1; v <= n; ++v) {
            fy[v] = c[1][v] - fx[1];
            for (int u = 1; u <= n; ++u) {
                fy[v] = min(fy[v], c[u][v] - fx[u]);
            }
        }
        for (int u = 1; u <= n; ++u) {
            start = u;
            initBFS();
            while (!finish) {
                findAugPath();
                if (!finish)
                    subX_addY();
            }
            Enlarge();
        }
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (c[i][l[i]] != inf)
                ans += c[i][l[i]];
            else
                l[i] = 0;
        }
        return ans;
    }
};

int32_t main() {
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    Hungarian M(n1, n2);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        M.add_edge(u, v, -w);
    }
    cout << -M.maximum_matching() << '\n';
    for (int i = 1; i <= n1; i++) cout << M.l[i] << ' ';
    return 0;
}
/*
There are n jobs and n workers. Each worker specifies 
the amount of money they expect for a particular job. 
Each worker can be assigned to only one job. 
The objective is to assign jobs to workers in a way 
that minimizes the total cost.
*/

/*
Given an  
n*n matrix A, the task is to find a permutation  
p of length n such that the value  
sum A[i][p[i]] is minimized.
*/
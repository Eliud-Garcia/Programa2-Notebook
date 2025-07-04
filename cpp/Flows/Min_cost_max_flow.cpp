#define INF 0x3f3f3f

template<typename T> struct mcmf {
    struct edge {
        int to, rev, flow, cap; // para, id da reversa, fluxo, capacidade
        bool res; // se eh reversa
        T cost; // custo da unidade de fluxo
        edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
        edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_)
            : to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
    };

    vector<vector<edge>> g;
    vi par_idx, par;
    T inf;
    vector<T> dist;

    mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}

    void add(int u, int v, int w, T cost) { // de u pra v com cap w e custo cost
        edge a = edge(v, sz(g[v]), 0, w, cost, false);
        edge b = edge(u, sz(g[u]), 0, 0, -cost, true);

        g[u].pb(a);
        g[v].pb(b);
    }

    vector<T> spfa(int s) { // nao precisa se nao tiver custo negativo
        deque<int> q;
        vb is_inside(sz(g), 0);
        dist = vector<T>(sz(g), inf);

        dist[s] = 0;
        q.pb(s);
        is_inside[s] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            is_inside[v] = false;

            for (int i = 0; i < sz(g[v]); i++) {
                auto [to, rev, flow, cap, res, cost] = g[v][i];
                if (flow < cap and dist[v] + cost < dist[to]) {
                    dist[to] = dist[v] + cost;

                    if (is_inside[to]) continue;
                    if (!q.empty() and dist[to] > dist[q.front()]) q.push_back(to);
                    else q.push_front(to);
                    is_inside[to] = true;
                }
            }
        }
        return dist;
    }
    bool dijkstra(int s, int t, vector<T>& pot) {
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        dist = vector<T>(sz(g), inf);
        dist[s] = 0;
        q.emplace(0, s);
        while (sz(q)) {
            auto [d, v] = q.top();
            q.pop();
            if (dist[v] < d) continue;
            for (int i = 0; i < sz(g[v]); i++) {
                auto [to, rev, flow, cap, res, cost] = g[v][i];
                cost += pot[v] - pot[to];
                if (flow < cap and dist[v] + cost < dist[to]) {
                    dist[to] = dist[v] + cost;
                    q.emplace(dist[to], to);
                    par_idx[to] = i, par[to] = v;
                }
            }
        }
        return dist[t] < inf;
    }

    pair<int, T> min_cost_flow(int s, int t, int flow = INF) {
        vector<T> pot(sz(g), 0);
        pot = spfa(s); // mudar algoritmo de caminho minimo aqui

        int f = 0;
        T ret = 0;
        while (f < flow and dijkstra(s, t, pot)) {
            for (int i = 0; i < sz(g); i++)
                if (dist[i] < inf) pot[i] += dist[i];

            int mn_flow = flow - f, u = t;
            while (u != s) {
                mn_flow = min(mn_flow,
                              g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
                u = par[u];
            }

            ret += pot[t] * mn_flow;

            u = t;
            while (u != s) {
                g[par[u]][par_idx[u]].flow += mn_flow;
                g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
                u = par[u];
            }

            f += mn_flow;
        }

        return make_pair(f, ret);
    }

    // Opcional: retorna as arestas originais por onde passa flow = cap
    vector<pair<int,int>> recover() {
        vector<pair<int,int>> used;
        for (int i = 0; i < sz(g); i++) for (edge e : g[i])
                if(e.flow == e.cap && !e.res) used.push_back({i, e.to});
        return used;
    }
};

//nodos = (n + m) + 10;
// s = n - 1;
// t = n - 2;

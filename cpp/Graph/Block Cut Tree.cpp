
//Block cut tree
/*
n originalmente es 2e5
pero está con 4e5 porque los ids
pueden ser mayores a n
*/
const int N = 4e5 + 5;

int timer, low[N], dis[N], art[N], tam;
vector<int> g[N], bcc[N], st;

void dfs(int u, int pre = 0) {
    low[u] = dis[u] = ++timer;
    st.push_back(u);
    for (auto v : g[u]) {
        if (!dis[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dis[u]) {
                tam++;
                int x;
                do {
                    x = st.back();
                    st.pop_back();
                    bcc[x].push_back(tam);
                } while (x ^ v);
                bcc[u].push_back(tam);
            }
        } else if (v != pre)
            low[u] = min(low[u], dis[v]);
    }
}

vector<int> bt[N]; // block cut tree
int id[N];

void build(int n) {
    dfs(1);
    for (int u = 1; u <= n; u++) {
        if (bcc[u].size() > 1) { // AP
            id[u] = ++tam;
            //si es un AP, entonces
            //en el arbol tambien es un AP
            art[id[u]] = 1; 
            for (auto v : bcc[u]) {
                bt[id[u]].push_back(v);
                bt[v].push_back(id[u]);
            }
        } else if (bcc[u].size() == 1)
            id[u] = bcc[u][0];
    }
}
//arbol queda indexado desde 1
//dfs_lca(u, p, d)

//lca(int u, int v)

//valida si c esta en el camino de (a, b)
bool on_path(int a, int b, int c){
    int ab = lca(a, b);
    int ac = lca(a, c);
    int bc = lca(b, c);

    if (ab == c || (ac == ab && bc == c) ||
        (bc == ab && ac == c)) {
        return true;
    }
    return false;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    build(n);
    dfs_lca(1, 0, 0);
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        bool on_p = on_path(id[a], id[b], id[c]);
        if((a == c) || (b == c) || (art[id[c]] && on_p)){
            cout << "NO" << ln;
        }else{
            cout << "YES" << ln;
        }
    }
    return 0;
    //https://cses.fi/problemset/task/1705
}
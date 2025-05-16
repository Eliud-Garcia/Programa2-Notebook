
//Segtree code here

const int MAXN = 2e5 + 5;
vi g[MAXN];
int val[MAXN]; // value of each node

vi st_val(MAXN, 0);
STree<int> st(st_val);

struct HLD {
    int n, timer;
    vi in, out, hp, tam;
    vi deep, par;

    HLD(int v, int n) {
        this->n = n;
        timer = 0;
        in.resize(n); //tin
        out.resize(n); //tout
        hp.resize(n); //heavy path
        tam.resize(n); //subtree size
        deep.resize(n); //depth
        par.resize(n); // parent

        dfs_sz(v, v);
        hp[v] = v;
        dfs_hld(v, v);
    }

    void dfs_sz(int u, int p){
        tam[u] = 1;
        par[u] = p;
        deep[u] = deep[p] + 1;
        for (auto &v : g[u]) {
            if(v == p) continue;
            dfs_sz(v, u);
            tam[u] += tam[v];
            if (tam[v] > tam[g[u][0]])
                swap(v, g[u][0]);
        }

    }

    void dfs_hld(int u, int p) {
        in[u] = timer++;
        st.upd(in[u], val[u]);
        for (auto &v : g[u]) {
            if(v == p) continue;
            hp[v] = v == g[u][0] ? hp[u] : v;
            dfs_hld(v, u);
        }
        out[u] = timer;
    }

    int path(int a, int b) { // query on path
        int ans = 0;
        while(hp[a] != hp[b]) {
            if(deep[hp[a]] < deep[hp[b]])swap(a, b);
            ans = max(ans, st.query(in[hp[a]], in[a]));
            a = par[hp[a]];
        }
        if(deep[a] > deep[b]) swap(a, b);
        ans = max(ans, st.query(in[a], in[b]));
        return ans;
    }
};

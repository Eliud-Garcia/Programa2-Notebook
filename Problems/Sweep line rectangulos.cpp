


// STree Lazy aqui con estas modificaciones

    /* STree(vector<T> &a) {
        n = sz(a);
        st.resize(n * 4);
        lazy.resize(n * 4, -1);
        build(1, 0, n - 1, a);
    }

    T oper(T a, T b) {
        return max(a, b);
    } */

    /*
    void push(int v, int tl, int tr) {
        if (lazy[v] == -1) return;
        st[v] = lazy[v];
        if (tl != tr) {
            lazy[v * 2] = lazy[v];
            lazy[v * 2 + 1] = lazy[v];
        }
        lazy[v] = -1;
    } */

struct event {
    int x, y, id, t;

    bool operator < (event &o) const {
        if(x == o.x) return t < o.t;
        return x < o.x;
    }
};

int n, m;
const int MAXN = 80005;
vector<array<int, 4>> rec(MAXN);
vector<array<int, 3>> pts(MAXN);
int parent[MAXN];
vi g[MAXN];
bool vis[MAXN];
int ans[MAXN];
set<int> dsu[MAXN];

vector<event> order;
vi compression;

int get_id(int x){
    return lower_bound(all(compression), x) - compression.begin();
}

set<int> dfs(int u, int p){
    if(vis[u]) return {};
    vis[u] = 1;
    set<int> a = dsu[u];

    for(int v: g[u]){
        if(!vis[v]){
            set<int> b = dfs(v, u);
            if(sz(a) < sz(b)) swap(a, b);

            for(int i: b){
                a.insert(i);
            }
        }
    }

    ans[u] = sz(a);
    return a;
}

int main() {
    cin >> n >> m;

    forab(i, 1, n + 1){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rec[i] = {x1, y1, x2, y2};

        order.pb({x1, y1, i, 0});
        order.pb({x2, y2, i, 2});


        compression.pb(y1);
        compression.pb(y2);
    }

    forab(i, 1, m + 1){
        int x, y, c;
        cin >> x >> y >> c;
        pts[i] = {x, y, c};

        order.pb({x, y, i, 1});

        compression.pb(y);
    }

    sort(all(order));


    sort(all(compression));
    compression.erase(unique(all(compression)), compression.end());

    vi aux(sz(compression) + 1, 0);

    forab(i, 1, n + 1) parent[i] = 0;

    STree<int> st(aux);

    for(auto [x, y, i, type] : order){
        if(type == 0){
            //rectangulo inicio
            auto [x1, y1, x2, y2] = rec[i];

            int l = get_id(y1);
            int r = get_id(y2);

            parent[i] = st.query(l, r);
            st.upd(l, r, i);

        }else if(type == 1){
            //punto
            int idx = get_id(y);
            int p = st.query(idx, idx);
            dsu[p].insert(pts[i][2]);

        }else{
            //rectangulo fin
            auto [x1, y1, x2, y2] = rec[i];

            int l = get_id(y1);
            int r = get_id(y2);

            st.upd(l, r, parent[i]);
        }
    }

    forab(i, 1, n + 1){
        g[parent[i]].pb(i);
        g[i].pb(parent[i]);
    }

    dfs(0, 0);

    forab(i, 1, n + 1) {
        cout << ans[i] << ln;
    }

    return 0;
}


//https://oj.uz/problem/view/COCI17_plahte

// Dan N rectangulos que NO se intersectan ni se tocan
// pero si pueden haber rectangulos contenidos en otros
// los rectangulos representan hojas de papel
// me dan dos puntos (x, y)
// uno para (esquina inferior izq)
//y otro para esquina superior derecha

// luego M bolas de colores son disparadas
// en coordenadas unicas (x, y, color)
// algunas caen dentro de rectangulos y otras por fuera

//cuando una bola cae en una hoja de papel, queda marcada
//en las hojas que estan debajo (contenidas)

// para cada hoja (rectangulo) decir cuantos colores diferentes
// contiene


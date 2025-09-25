
// Camino de Euler / Ciclo de Euler

//Validar que el ciclo inicie con el mismo src
//Validar que el camino termine con n - 1 en caso de ser obligatorio

// Declarar: 'euler<true> E(n);' si se desea
// dirigido y con 'n' vértices.
// Las funciones devuelven un par con un booleano
// que indica si tiene el ciclo/camino solicitado,
// y un vector de {vértice, ID de la arista para alcanzar el vértice}.
// Si es get_path, en la primera posición el ID será -1.
// get_path(src) intenta encontrar un camino o ciclo euleriano
// comenzando en el vértice 'src'.
// Si encuentra un ciclo, el primer y el último vértice serán 'src'.
// Si es un P3, un posible retorno sería [0, 1, 2, 0]
// get_cycle() encuentra un ciclo euleriano si el grafo es euleriano.
// Si es un P3, un posible retorno sería [0, 1, 2]
// (el vértice inicial no se repite).

// O(n+m)

using pii = pair<int, int>;

template <bool directed = false>
struct euler {
    int n;
    vector<vector<pii>> g;
    vi used;

    euler(int n_) : n(n_), g(n) {}
    void add(int a, int b) {
        int at = sz(used);
        used.push_back(0);
        g[a].emplace_back(b, at);
        if(!directed) g[b].emplace_back(a, at);
    }
    // #warning chamar para o src certo!
    pair<bool, vector<pii>> get_path(int src) {
        if(!sz(used)) return {true, {}};
        vi beg(n, 0);
        for(int& i : used) i = 0;
        // {{vertice, anterior}, label}
        vector<pair<pii, int>> ret, st = {{{src, -1}, -1}};
        while(sz(st)) {
            int at = st.back().first.first;
            int& it = beg[at];
            while(it < sz(g[at]) and used[g[at][it].second]) it++;
            if(it == sz(g[at])) {
                if(sz(ret) and ret.back().first.second != at)
                    return {false, {}};
                ret.push_back(st.back()), st.pop_back();
            } else {
                st.push_back({{g[at][it].first, at}, g[at][it].second});
                used[g[at][it].second] = 1;
            }
        }
        if(sz(ret) != sz(used) + 1) return {false, {}};
        vector<pii> ans;
        for(auto i : ret) ans.emplace_back(i.first.first, i.second);
        reverse(all(ans));
        return {true, ans};
    }
    pair<bool, vector<pii>> get_cycle() {
        if(!sz(used)) return {true, {}};
        int src = 0;
        while(!sz(g[src])) src++;
        auto ans = get_path(src);
        if(!ans.first or ans.second[0].first != ans.second.back().first)
            return {false, {}};
        ans.second[0].second = ans.second.back().second;
        ans.second.pop_back();
        return ans;
    }
};

int main() {
    int nodos, m;
    cin >> nodos >> m;
    euler<true> ee(nodos);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        ee.add(a, b); // agregar arista
    }

    pair<bool, vector<pii>> ans = ee.get_path(0);
    //se valida que haya camino y que termine en n - 1
    if(ans.first && ans.second.back().first == n - 1) {
        for(auto [u, id] : ans.second) {
            cout << u + 1 << " ";
        }
        cout << ln;
    } else {
        cout << "IMPOSSIBLE" << ln;
    }
    return 0;
}

/*
    EULERIAN PATH
    Un camino euleriano es un camino de aristas
    que visita todas las aristas de un grafo
    exactamente una vez.

    UNDIRECTED GRAPH

    o bien cada vertice tiene un grado par o
    exactamente dos vertices tienen un grado impar.

    DIRECTED GRAPH

    como máximo un vértice tiene (grado de salida) - (grado de entrada) = 1
    y como máximo un vértice tiene (grado de entrada) - (grado de salida) = 1,
    y todos los demás vértices tienen grados de entrada y salida iguales.
*/

// EULERIAN PATH DIRECTED GRAPH  O(E)

/*
    Eulerian CIRCUIT
    Un circuito euleriano es un camino euleriano
    que comienza y termina en el mismo vértice.

    UNDIRECTED GRAPH

    Cada vertice tiene un grado par.

    DIRECTED GRAPH

    Cada vértice tiene el mismo grado de entrada y de salida.
*/

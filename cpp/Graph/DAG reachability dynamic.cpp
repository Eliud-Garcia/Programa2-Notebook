

//Tomado de :
// https://github.com/ShahjalalShohag/code-library/blob/main/Graph%20Theory/DAG%20Reachability%20Dynamic.cpp

/*add_edge(s, t): insert edge (s,t) to the network if it does not make a cycle
is_reachable(s, t): return true iff there is a path s --> t
Algorithm by G.F. ITALIANO
Complexity: amortized O(n) per update*/
// 0-indexed
struct Italiano {
    int n;
    vector<vector<int>> par;
    vector<vector<vector<int>>> child;
    Italiano(int n)
        : n(n), par(n, vector<int>(n, -1)), child(n, vector<vector<int>>(n)) {}
    bool is_reachable(int s, int t) { return s == t || par[s][t] >= 0; }
    bool add_edge(int s, int t) {
        if (is_reachable(t, s))
            return 0; // break DAG condition
        if (is_reachable(s, t))
            return 1; // no-modification performed
        for (int p = 0; p < n; ++p) {
            if (is_reachable(p, s) && !is_reachable(p, t))
                meld(p, t, s, t);
        }
        return 1;
    }
    void meld(int root, int sub, int u, int v) {
        par[root][v] = u;
        child[root][u].push_back(v);
        for (int c : child[sub][v]) {
            if (!is_reachable(root, c))
                meld(root, sub, v, c);
        }
    }
};

// add edges one by one. if it breaks DAG law then print it

int main() {
    int n, m;
    cin >> n >> m;
    Italiano t(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        if (t.is_reachable(v, u))
            cout << u + 1 << " " << v + 1 << ln;
        else
            t.add_edge(u, v);
    }
    cout << "0 0" << ln;
    return 0;
}

/*
    dado una lista de aristas dirigidas
    agregar solo las necesarias para que no hayan ciclos

    decir cuales aristas NO fueron agregadas
*/


struct mbm {// O(E * sqrt(V))
    int n, m; //left and right sz
    vi mat, inv, d;
    vector<vi> g;
    vb cover[2];

    mbm(int nl, int nr) : n(nl), m(nr) {
        mat = vi(n, -1);
        inv = vi(m, -1);

        d = vi(n);
        g = vector<vi>(n);

        //mvc
        cover[0].assign(n, true);
        cover[1].assign(m, false);
    }
    //u->[0, n)  v->[0, m)
    void add(int u, int v) {
        g[u].pb(v);
    }

    bool bfs() {
        bool aug = false;
        queue<int> q;
        forab(u, 0,n) if (mat[u] < 0) q.push(u);
        else d[u] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (inv[v] < 0) aug = true;
                else if (d[inv[v]] < 0) d[inv[v]] = d[u] + 1, q.push(inv[v]);
            }
        }
        return aug;
    }

    bool dfs(int u) {
        for (auto v : g[u]) if (inv[v] < 0) {
                mat[u] = v, inv[v] = u;
                return true;
            }
        for (auto v : g[u]) if (d[inv[v]] > d[u] && dfs(inv[v])) {
                mat[u] = v, inv[v] = u;
                return true;
            }
        d[u] = 0;
        return false;
    }

    int go() {
        int ans = 0;
        while (bfs()) forab(u,0,n) if (mat[u] < 0) ans += dfs(u);
        return ans;
    }
    void dfs2(int u) {
        cover[0][u] = false;
        for (auto v : g[u]) if (!cover[1][v]) {
                cover[1][v] = true;
                dfs2(inv[v]);
            }
    }
    pair<vi, vi> mvc() {
        int mf = go();
        forab(u, 0,n) if (mat[u] < 0) dfs2(u);
        vi L, R;
        forab(i, 0, n) if (cover[0][i]) L.pb(i);
        forab(i, 0, m) if (cover[1][i]) R.pb(i);
        assert(mf == sz(L) + sz(R));
        return {L, R};
    }

};

int main() {
    //get matching
    forab(u, 0, n) {
        if(dd.mat[u] != -1) {
            cout << u + 1 << " " << dd.mat[u] + 1 << ln;
        }
    }
    return 0;
}

/*Maximum Independent Set:
Subset of nodes
with the following propriety:
For any two nodes u, v
are not adjacent
(There is no direct edge between nodes  u and  v).
*/

/*Minimum Vertex Cover:
A vertex cover is a subset of the nodes
that together touch all the edges.
*/

//Max Independet Set = |V| - size of the MCBM

/*Min Path Cover (only in DAG)
 Find the minimum number of paths to cover
 each vertex on a graph

 find the transitive clousure (reachability) with a bitset
 add edge u -> v if you can reach v from u

 ans = (#node - matching)
 */

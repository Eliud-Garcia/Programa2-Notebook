const ll oo = 1e18 / 10;
int main(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<vll> g(n, vll(n));
    forn(i, n){
        forab(j, i + 1, n){
            g[i][j] = g[j][i] = oo;
        }
    }
    int a, b;
    ll w;
    forn(i, m){
        cin >> a >> b >> w;
        a--;b--;
        g[a][b] = g[b][a] = min(g[a][b], w);
    }
    //Floyd Warshall O(n^3)
    forn(k, n){
        forn (i, n) {
            forn (j, n) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    while(q--){
        cin >> a >> b;
        a--;b--;
        cout << (g[a][b] == oo ? -1: g[a][b]) <<ln;
    }
    return 0;
}
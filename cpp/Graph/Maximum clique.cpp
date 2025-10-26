

const int MAXN = 51;

int g[MAXN][MAXN];
int res;
ll edges[MAXN];
// 3 ^ (n / 3)
void BronKerbosch(int n, ll R, ll P, ll X) {
    if (P == 0LL && X == 0LL) { // here we will find all possible maximal
                                // cliques (not maximum) i.e. there is no node
                                // which can be included in this set
        int t = __builtin_popcountll(R);
        res = max(res, t);
        return;
    }

    int u = 0;
    while (!((1LL << u) & (P | X))) u++;
    for (int v = 0; v < n; v++) {
        if (((1LL << v) & P) && !((1LL << v) & edges[u])) {
            BronKerbosch(n, R | (1LL << v), P & edges[v], X & edges[v]);
            P -= (1LL << v);
            X |= (1LL << v);
        }
    }
}

int max_clique(int n) {
    res = 0;
    for (int i = 1; i <= n; i++) {
        edges[i - 1] = 0;
        for (int j = 1; j <= n; j++)
            if (g[i][j])
                edges[i - 1] |= (1LL << (j - 1));
    }
    BronKerbosch(n, 0, (1LL << n) - 1, 0);
    return res;
}

int main() {
    int n;
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<ll> a(n + 1);

        memset(edges, 0, sizeof edges);
        memset(g, 0, sizeof g);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j)
                    continue;
                if (__gcd(a[i], a[j]) == 1) {
                    g[i][j] = 1;
                    g[j][i] = 1;
                }
            }
        }

        int ans = max_clique(n);
        cout << ans << endl;
    }
}

/*
subgrafo completo
*/

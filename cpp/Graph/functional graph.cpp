

const int MAXN = 2e5 + 5;
vi rg[MAXN]; // reverse graph
vll valor(MAXN);
vb vis(MAXN, 0);
vi p(MAXN); //parent
vi in_cycle(MAXN, 0);

void mark(int u) {
    if(vis[u]) return;
    vis[u] = 1;
    for(int v: rg[u]) {
        mark(v);
    }
}

int cycle(int u) {
    int x = p[u];
    int y = p[p[u]];
    while(x != y) {
        x = p[x];
        y = p[p[y]];
    }
    //traverse the cycle
    ll min_cycle = valor[x];
    x = p[x];
    while(x != y) {
        in_cycle[x] = 1;
        min_cycle = min(min_cycle, valor[x]);
        x = p[x];
    }
    mark(x);
    return min_cycle;
}

int main() {
    int n;
    cin >> n;
    forab(i, 1, n + 1) {
        cin >> valor[i];
    }

    forab(i, 1, n + 1) {
        cin >> p[i];
        rg[p[i]].pb(i);
    }

    ll ans = 0;
    forab(i, 1, n + 1) {
        if(!vis[i]) {
            ans += cycle(i);
        }
    }
    cout << ans << ln;
    return 0;
}

//When we are swapping 2
//elements that belong to one cycle,
//we are splitting our cycle into 2
//parts.

//min swaps(a[i], a[a[i]]) to sort
//the permutation = n - #cycles

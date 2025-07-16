
using ii = pair<int, int>;

int n;
const int MAXN = 2e5 + 5;
vi g[MAXN];

ii dfs(int u, int p){
    ii ans = make_pair(0, u);
    for(int v: g[u]){
        if(v == p) continue;
        ans = max(ans, dfs(v, u));
    }
    ans.first++;
    return ans;
}

int main() {
    auto [dis, nodo] = dfs(1, 0);
    auto [diam, raiz] = dfs(nodo, 0);

    cout << diam - 1 << ln;
    return 0;
}

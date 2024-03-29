const int MAXN = 3e5 + 5;
vi g[MAXN];
vb vis(MAXN, 0);
vi dis(MAXN, 0);
int n, m;
int nodoLejano, maxDis;
void bfs(int src){
    vis = vb(n + 1, 0);
    dis = vi(n + 1);
    queue<int> q;
    vis[src] = 1;
    nodoLejano = src;
    q.push(src);
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(dis[u] > maxDis){
            nodoLejano = u;
            maxDis = dis[u];
        }
        for(int v: g[u]){
            if(!vis[v]){
                vis[v] = 1;
                dis[v] = dis[u] + dis[v] + 1;
                q.push(v);
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int a, b;
    forn(i, n - 1){
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    maxDis = 0;
    bfs(1);
    bfs(nodoLejano);
    cout << maxDis << ln;
    return 0;
}
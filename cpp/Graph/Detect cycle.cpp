
//directed graph
const int MAXN = 2e5 + 5;
vi g[MAXN];
int color[MAXN];
int in_cycle[MAXN];
int par[MAXN];

void dfs(int u){
    if(color[u] == 2) return;
    color[u] = 1;
    for(int v: g[u]){
        if(color[v] == 0){
            par[v] = u;
            dfs(v);
        }else if(color[v] == 1){
            //traverse the cycle
            int ini = u, fin = v;
            int cur = u;
            in_cycle[cur] = 1;
            while(cur != v){
                cur = par[cur];
                in_cycle[cur] = 1;
            }
            in_cycle[v] = 1;
        }
    }
    color[u] = 2;
}

/*
    forab(i, 1, n + 1) {
        in_cycle[i] = 0;
        color[i] = 0;
    }
    forab(i, 1, n + 1) {
        if(color[i] == 0) dfs(i);
    }
*/

//undirected graph
const int MAXN = 2e5 + 5;
int color[MAXN];
int mark[MAXN];
int par[MAXN];
vi g[MAXN];

void dfs(int u, int p, int &cy){
    if(color[u] == 2){
        return;
    }
    if(color[u] == 1){
        cy++;
        int cur = p;
        mark[cur] = cy;
        while(cur != u){
            cur = par[cur];
            mark[cur] = cy;
        }
        return;
    }
    par[u] = p;
    color[u] = 1;
    for(int v: g[u]){
        if(v == par[u]) continue;
        dfs(v, u, cy);
    }
    color[u] = 2;
}

/*
    forab(i, 1, n + 1){
        color[i] = 0;
        par[i] = i;
        mark[i] = -1;
    }
    int cycles = 0;
    dfs(1, 1, cycles);

    forab(i, 1, n + 1){
        if(mark[i] != -1){
            found = true;
        }
    }
*/

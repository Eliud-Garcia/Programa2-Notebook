//Kuhn's

const int MAXN = 100;
int vis[MAXN];
int match[MAXN];

//from left to right
vector<int> g[MAXN];

//O(n * m)   O(n³)
int dfs(int u){
    for(int v: g[u]){
        if(vis[v]) continue;
        vis[v] = 1;
        if(match[v] == -1 || dfs(match[v])){
            match[v] = u;
            return 1;
        } 
    }
    return 0;
}

int go(){
    int ans = 0;
    memset(match, -1, sizeof match);
    for(int i = 0; i < MAXN; i++){
        memset(vis, 0, sizeof vis);
        if(dfs(i)) ans++;
    }
    return ans;
}

/*
    int u, v
    g[u].push_back(v);

    u - left part
    v - right par
*/
#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define ll long long
#define forn(i, n) for(int i = 0; i< n; i++)
#define vi vector<int>
#define vbool vector<bool>
#define pb push_back

vector<vi> g;
vi color;
vi ans;

bool bipartite = 1;

void dfs(int node, int c){
    if(~color[node]){
        if(color[node] ^ c){
            bipartite = 0;
        }
        return;
    }

    color[node] = c;
    for(int next: g[node]){
        dfs(next, c^1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.assign(n + 1, vi());
    color.assign(n + 1, -1);
    int a, b;
    forn(i, m){
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    for(int i = 1; i < n + 1 && bipartite; i++){
        if(color[i] < 0){
            dfs(i, 1);
        }
    }
    if(bipartite){
        for(int i = 1; i <n + 1; i++){
            cout << color[i] + 1 <<" ";
        }
        
    }else{
        cout << "-1" << ln;
    }
    
    return 0;
}
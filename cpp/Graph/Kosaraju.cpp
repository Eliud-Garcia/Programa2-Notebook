#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define forn(i, n) for(int i = 0; i < n; i++)
#define forab(i, a, b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;

//Kosaraju
//numero de componentes fuertemente conexas = tag
const int MAXN = (int)1e5+ 5;
vi g[MAXN];
vi rg[MAXN];
vb vis(MAXN), id(MAXN);
int tag;
void dfs1(int u, stack<int> &st){
    vis[u] = 1;
    for(int v : g[u]){
        if(!vis[v]){
            dfs1(v, st);
        }
    }
    st.push(u);
}

void dfs2(int u){
    vis[u] = 1;
    id[u] = tag;
    cout << u << " ";
    for(int v: rg[u]){
        if(!vis[v]){
            dfs2(v);
        }
    }
}
int n, m;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    int a, b;
    forn(i, m){
        cin >> a >> b;
        g[a].pb(b);
        rg[b].pb(a);
    }

    stack<int> st;
    forab(i, 1, n + 1){
        if(!vis[i]){
            dfs1(i, st);
        }
    }
    vis = vb(n + 1, 0);
    //componentes en orden topologico
    while(!st.empty()){
        int u = st.top(); st.pop();
        if(vis[u]) continue;
        tag++;
        cout << "componente #" << tag << " : ";
        dfs2(u);
        cout << ln;
    }
    

    
    return 0;
}
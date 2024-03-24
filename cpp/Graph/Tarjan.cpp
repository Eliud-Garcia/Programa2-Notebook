
int n, m;
const int MAXN = 1e5 + 5;
vi g[MAXN];

struct Tarjan {
  vi low, num, comp;
  stack<int> st;
  int n, scc, cont;
  const int oo = int(1e9);
  
  Tarjan(int n) {
    this->n = n;
    low.resize(n);
    num.assign(n, -1);
    comp.resize(n);
    scc = cont = 0;
  }
  
  void dfs(int v) {
    low[v] = num[v] = cont++;
    st.push(v);
    for (int &u : g[v]) {
      if (num[u] == -1) dfs(u);
      low[v] = min(low[v], low[u]);
    }
    if (low[v] == num[v]) {
      int u;
      do {
        u = st.top(); st.pop();
        low[u] = oo;
        comp[u] = scc;
      } while (u != v);
      scc++;
    }
  };
  
  vector<vi> getComp(){
    forab (i, 1,  n)
      if (num[i] == -1) dfs(i);
    vector<vi> cc(scc);
    forab(i, 1, n){
       cc[comp[i]].pb(i);
    }
    return cc;
  }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    int a, b;
    forn(i, m){
        cin >> a >> b;
        g[a].pb(b);
    }
    Tarjan t(n + 1);
    vector<vi> components = t.getComp();
    for(vi cc: components){
        for(int u: cc){
            cout << u << " ";
        }
        cout << ln;
    }
    return 0;
}
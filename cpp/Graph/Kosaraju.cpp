
const int MAXN = (int)1e5+ 5;
vi g[MAXN];
vi rg[MAXN];
vb vis(MAXN), id(MAXN);
int tag;
vector<vi> comp;
void dfs1(int u, stack<int> &st){
	vis[u] = 1;
	for(int v : g[u]){
		if(!vis[v]) dfs1(v, st);
	}
	st.push(u);
}

void dfs2(int u){
	vis[u] = 1;
	id[u] = tag;
	comp.back().pb(u);
	//u esta en la componente id[u]
	for(int v: rg[u]){
		if(!vis[v]) dfs2(v);
	}
}
int n, m;
int main(){
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
		comp.pb({});
		dfs2(u);
	}

	int cp = 1;
	for(auto i : comp){
		cout << "componente #" << cp <<" : ";
		for(auto j: i){
			cout << j << " ";
		}
		cout << ln;
	}
	return 0;
}
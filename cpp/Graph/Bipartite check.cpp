const int N = 2e5+5;
vi g[N];
vi color;
bool bipartite = 1;

void dfs(int u, int c) {
   if(~color[u]) {
      if(color[u] ^ c) {
         bipartite = 0;
      }
      return;
   }
   color[u] = c;
   for(int next: g[u]) {
      dfs(next, c^1);
   }
}

int main() {
   int n, m;
   cin >> n >> m;
   color = vi(n + 1, -1);
   int a, b;
   forn(i, m) {
      cin >> a >> b;
      g[a].pb(b);
      g[b].pb(a);
   }
   for(int i = 1; i < n + 1 && bipartite; i++) {
      if(color[i] < 0) dfs(i, 1);
   }
   if(bipartite) {
      //color of each node
      forab(i, 1, n + 1) {
         cout << color[i] + 1 <<" ";
      }
   } else {
      cout << "No bipartite" << ln;
   }
   return 0;
}

/*validar distancias
entre dos nodos A y B
si es par o impar
if(!bipartite){
	dist pares e impares;
}else{
	if(color[a] == color[b]){
		dist par
	}
	if(color[a] != color[b]){
		dist impar
	}
}*/

vi topo_sort(vi &grado) {
  vi topo;
  queue<int> q;
  forab(i, 1, n + 1)
    if(grado[i] == 0) q.push(i);
  while(sz(q)){
    int u = q.front();
    q.pop();
    topo.pb(u);
    for(int v: g[u]){
      if(--grado[v] == 0){
        q.push(v);
      }
    }
  }
  if(sz(topo) == n) return topo;
  else return vi();
}
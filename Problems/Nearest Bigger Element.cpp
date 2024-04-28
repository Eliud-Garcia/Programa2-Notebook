
//poner esta funcion dentro del segTree
//oper = max
void nearestBiggerElem(int v, int tl, int tr, T val) {
  if(tl == tr) {
    st[v] -=val;
    cout << tl + 1 <<" ";
    return;
  }
  int tm = (tr + tl) / 2;
  if(st[v * 2] >= val) nearestBiggerElem(v * 2, tl, tm, val);
  else nearestBiggerElem(v * 2 + 1, tm + 1, tr,  val);
  st[v] = oper(st[v * 2], st[v * 2 + 1]);
}

int main(){
  int n, m;
  cin >> n >> m;
  vi h(n);
  vi t(m);
  for(auto &i : h) cin >> i;
  for(auto &i : t) cin >> i;
  STree<int> st(h);
  forn(i, m){
    int val = t[i];
    int l = 0;
    int r = n - 1;
    if(st.st[1] < val) cout << 0 << " ";
    else st.nearestBiggerElem(1, l, r, val);
  }
  return 0;
}
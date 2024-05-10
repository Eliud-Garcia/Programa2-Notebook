//hay una rana i que salta de a[i] en a[i]
//decir por cual hoja pasaron mas ranas
void ocurrencia_multiplos(vi a) { //O(nlogn)
  int n = sz(a);
  vi occ(n + 1);
  unordered_map<int, int> mp;
  forn(i, n) {
    if (a[i] <= n) {
      mp[a[i]]++;
    }
  }
  forab(i, 1, n + 1) {
    if (mp[i] == 0) continue;
    form(j, i, n + 1, i) {
      occ[j]+=mp[i];
    }
  }
  /* multiplo mas repetido y menos repetido */
  ll MAX = 0;
  ll MIN = 1e18;
  for (ll i : occ) {
    MAX = max(MAX, i);
    MIN = min(MIN, i);
  }
}

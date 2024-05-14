vector<vi> prefix(string &s) {
  vector<vi> psa(26, vi(sz(s) + 1));
  forab(i, 1, sz(s) + 1) {
    forn(j, 26) {
      psa[j][i] = psa[j][i - 1];
    }
    char c = s[i - 1];
    psa[c - 'a'][i]++;
  }
  return psa;
}
//freq de char c en el rango [l, r]
//int query = psa[c -'a'][r] - psa[c-'a'][l];

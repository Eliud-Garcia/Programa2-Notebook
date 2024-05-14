
  //numero de substrings
  //que son palindromos
  //en el rango [l, r]
  string s; cin >> s;
  int n = sz(s);
  const int MAXN = 5000 + 10;
  vector<vb> isPal(MAXN, vb(MAXN));
  vector<vi> dp(MAXN, vi(MAXN));
  forn(i, n){
    isPal[i][i] = 1;
    dp[i][i] = 1;
    isPal[i + 1][i] = 1;
  }
  forab(len, 2, n + 1){
    forn(i, n - len + 1){
      isPal[i][i + len - 1] = isPal[i + 1][i + len - 2] & s[i] == s[i + len - 1];
      dp[i][i + len - 1] = dp[i][i + len - 2] +
      dp[i + 1][i + len - 1] - dp[i + 1][i + len - 2] +
       isPal[i][i + len - 1];
    }
  }
  int q; cin >> q;
  while(q--){
    int l, r; cin >> l >> r;
    l--; r--;
    cout << dp[l][r] << ln;
  }

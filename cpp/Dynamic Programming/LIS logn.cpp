
//longest increasing subsecuence
//O(n log n)
const ll oo = 1e18;
int main() {
  int n;
  cin >> n;
  vll a(n);
  for(auto &i: a) cin >> i;
  vll dp(n + 1, oo);
  dp[0] = -oo;
  forab(i, 0, n) {
    int l = upper_bound(all(dp), a[i]) - dp.begin();
    if(dp[l - 1] < a[i] && a[i] < dp[l]) {
      dp[l] = a[i];
    }
  }
  ll ans = 0;
  forab(l, 0, n + 1) {
    if(dp[l] < oo) ans = l;
  }
  cout << ans << ln;
  return 0;
}

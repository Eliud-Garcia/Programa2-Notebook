//we have two integers N and M,
//we need to find how many numbers
// obtained by rearranging
//digits of N are divisible by M.

int getdigit(char c) {
  return int(c - '0');
}

string s;
ll m;
ll dp[101][(1 << 18) + 1];
ll base = 10;

// go(0, 0);
ll go(ll rem, int mask) {
  if(rem == 0LL && mask == ((1 << sz(s)) - 1)) {
    return 1;
  }
  if(dp[rem][mask] != -1) return dp[rem][mask];
  ll ans = 0;
  forn(i, sz(s)) {
    if(!(mask & (1 << i))) {
      int digit = getdigit(s[i]);
      //leading zeros
      if(mask == 0 && digit == 0) continue;
      ans += go(((rem * base) + digit) % m, mask | (1 << i));
    }
  }
  return dp[rem][mask] = ans;
}

int main() {
  cin >> s >> m;
  vi cnt(10, 0);
  ll repetidos = 1;
  for(char c: s) {
    repetidos *= ++cnt[c - '0'];
  }
  vector<vll> dp(101, vll(1 << 18, 0));
  dp[0][0] = 1LL;
  forn(mask, (1 << sz(s))) {
    forn(i, sz(s)) {
      if(!(mask & (1 << i))) {
        int digit = getdigit(s[i]);
        if(mask == 0 && digit == 0) continue;
        forn(rem, m) {
          dp[((1LL * rem * base) + digit) % m][mask | (1 << i)] += dp[rem][mask];
        }
      }
    }
  }
  ll ans = dp[0][(1 << sz(s))- 1];
  cout << (ans / repetidos) << ln;
  return 0;
}

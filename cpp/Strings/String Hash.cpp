
//String hashing:
//Get polynomial hash for any substring in O(1) after O(n)
//preprocessing.

//Good values c = 137, mod = 10^9 + 7.
//				   , mod = 1e18 + 9.
struct hash_str {
  ll c, mod;
  vll h, p;
  hash_str(const string &s, ll c, ll mod) : c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1) {
    p[0] = 1;
    h[0] = 0;
    forn (i, sz(s)) {
      h[i + 1] = (c * h[i] + s[i]) % mod;
      p[i + 1] = (c * p[i]) % mod;
    }
  }
  // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
  ll get(int a, int b) {
    return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
  }
};

//example
string a, b;
cin >> a >> b;
ll mod = (long)1e9 + 7;
hash_i aa(a, 131, mod);
hash_i bb(b, 131, mod);

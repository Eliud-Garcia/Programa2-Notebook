
// define MOD
ll MOD = 1e9 + 7;

//use binpow() method here

const int MAXN = 1e6 + 1;
ll fact[MAXN];
ll ifact[MAXN];

void cal_factorials(int n){
  fact[0] = fact[1] = 1;
  for (int i = 2; i <= n; i++) {
    fact[i] = (fact[i - 1] * i) % MOD;
  }

  //fact_inv O(n)
  ifact[n] = binpow(fact[n], MOD - 2);
  for (int i = n - 1; i >= 0; i--) {
    ifact[i] = ((i + 1) * ifact[i + 1]) % MOD;
  }
}

ll binomial_coefficient(int n, int k) {
  return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int main() {
  int t; cin >> t;
  int caso = 1;
  cal_factorials(MAXN);
  while(t--){
    int n, k;
    cin >> n >> k;
    ll ans = binomial_coefficient(n, k);
    printf("Case %d: %lld\n", caso++, ans);
  }
  return 0;
}
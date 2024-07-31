
ll MOD = 1e9 + 7;

ll inv_mod(ll a){
  //binpow con MOD igual
  return binpow(a, MOD - 2);
}

ll suma(ll a, ll b){
  return ((a % MOD) + (b % MOD)) % MOD;
}

ll resta(ll a, ll b){
  return ((a % MOD) - (b % MOD) + MOD) % MOD;
}

ll multi(ll a, ll b){
  return ((a % MOD) * (b % MOD)) % MOD;
}

ll divi(ll a, ll b){
  return multi(a, inv_mod(b));
}

//GCD
ll gcd(ll a, ll b) {
  return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
}
//LCM
ll lcm(ll a, ll b) {
  ll lcm = (a / gcd(a, b)) * b;
  return lcm > 0 ? lcm : -lcm;
}
//lcm(A, B, C, ....) = 
//p1 max(a1, b1, c1, ...) * 
//p2 max(a2, b2, c2, ...) * 
//p3 max(a3, b3, c3, ...) * ... ...* pk max(ak, bk, ck, ...)
//pi = prime, ai = exponent

//cuantas veces B puede restar a A
x = floor(A/B + 0.0)

//distancia de X a Y dando saltos de tamaño D
int dis(int x, int y, int d) {
  return (abs(x - y) + (d - 1)) / d;
}


typedef unsigned long long ull;

int phi(int n) {
  int result = n;
  for(int i = 2; i * i <= n; ++i) {
    if(n % i) continue;
    while(n % i == 0)
      n /= i;
    result -= result / i;
  }

  if(n > 1) result -= result / n;
  return result;
}

//number of integers
//which are coprime
//gcd(a, b) == 1

vi phi_1_to_n(int n) {
  vi phi;
  forab(i, 0, n + 1) phi.pb(i);

  for(int i = 2; i <= n; ++i) {
    if(phi[i] != i) continue;

    for(int j = i; j <= n; j += i)
      phi[j] -= phi[j] / i;
  }
  return phi;
}

vi phi_1_to_n2(int n) {
  vi phi;
  forab(i, 0, n + 1) phi.pb(i - 1);
  phi[1] = 1;

  for(int i = 2; i <= n; ++i) {
    for(int j = i * 2; j <= n; j += i)
      phi[j] -= phi[i];
  }
  return phi;
}


int main() {
  int t; cin >> t;
  int caso = 1;
  int MAXN = 5e6;

  vi phi = phi_1_to_n(MAXN);

  //sumatoria en rango de ph[i] * phi[i]
  vector<ull> pf(MAXN + 1, 0);
  forab(i, 2, MAXN + 1){
    pf[i] = pf[i - 1] + (ull(phi[i]) * ull(phi[i]));
  }

  while(t--){
    int a, b;
    cin >> a >> b;
    ull ans = pf[b] - pf[a - 1];
    printf("Case %d: %llu\n", caso++, ans);
  }
  return 0;
}

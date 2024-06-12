
ll euclid(ll a, ll b, ll &x, ll &y) {
  if(b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll xi, yi;
  ll g = euclid(b, a % b, xi, yi);
  x = yi;
  y = xi  - yi * (a / b);
  return g;
}

int main() {
  //hallar Ax + By + C = 0
  ll a, b, c;
  cin >> a >> b >> c;
  ll x, y;
  ll g = euclid(a, b, x, y);
  if(c % g) cout << "-1" << ln;
  else cout << (-(c / g) * x) << " " << (-(c / g) * y) << ln;
  return 0;
}

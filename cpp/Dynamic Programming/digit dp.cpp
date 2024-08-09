//digit dp
//[0, a]
const int MAXDIGT = 20;
int num[MAXDIGT];
pair<ll, ll> dp[MAXDIGT][2];
int n; // number of digits
int k;

//What if we want [a, b]
//ans(b) - ans(a - 1)

pair<ll, ll> go(int idx, bool is_eq){
  if(dp[idx][is_eq].first != -1) return dp[idx][is_eq];
  if(idx == n) return {1, 0};

  ll cont = 0, sum = 0;
  for(int i = 0; i <= (is_eq ? num[idx] : 9); i++){
    pair<ll, ll> cur =  go(idx + 1, is_eq && i == num[idx]);
    cont += cur.first;
    sum += cur.second + cur.first * i;
  }
  return dp[idx][is_eq] = {cont, sum};
}

ll solve(ll x){
  string aux = to_string(x);
  n = sz(aux);
  forn(i, n) num[i] = (aux[i] - '0');
  memset(dp, -1, sizeof dp);
  return go(0, 1).second;
}

int main() {
  while(true){
    ll a, b; cin >> a >> b;
    if(a < 0 && b < 0) break;
    ll aa = solve(a - 1);
    ll bb = solve(b);
    cout << bb - aa << ln;
  }
  return 0;
}

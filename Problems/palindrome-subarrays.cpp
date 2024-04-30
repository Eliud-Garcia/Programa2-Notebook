
//dada una cadena s
//contar los subarrays [l, r]
//donde organizando las letras
//se puede formar un palindromo
int n; // 1e6
string s;
const int MASK = 1 << 26;
int feq[MASK];

int main(){
  cin >> n;
  cin >> s;
  feq[0]+=1;
  ll ans = 0;
  int cur_mask = 0;
  forab(r, 1, n + 1){
    cur_mask ^= 1 << (s[r - 1] - 'a');
    ans+=feq[cur_mask]; // caso par
    forn(i, 26){
      ans+=feq[cur_mask ^ (1 << i)]; // caso impar
    }
    feq[cur_mask]+=1;
  }
  cout << ans << ln;
  return 0;
}
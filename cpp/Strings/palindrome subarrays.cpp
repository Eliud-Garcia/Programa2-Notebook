
// how many subarrays s[l,r]
// exists such that you
//can reorder its characters
// to get a palindrome.
const int N = 1e6 + 5;
const int MASK = (1<<26);
int F[MASK];

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  ll ans = 0;
  int cur_mask = 0;
  F[0]++;
  forn(r, n) {
    cur_mask ^= 1 <<(s[r] - 'a');
    ans+=F[cur_mask];//caso par
    forn(y, 26) {
      ans+=F[cur_mask ^ (1 << y)];//caso impar
    }
    F[cur_mask]++;
  }
  cout << ans << ln;
  return 0;
}

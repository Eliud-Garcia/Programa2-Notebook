
const int MAX_N = 101;
const int MAX_SUM = 1e5 + 1;
bool dp[MAX_N + 1][MAX_SUM + 1];

int main(){
  //dada una cantidad de monedas, decir todas
  //sumas que se pueden formar con ellas
  int n;
	cin >> n;
	vi coins(n);
	for(auto &i: coins) cin >> i;
	dp[0][0] = true;
	forab (i, 1, n + 1) {
		forab (curSum, 0, MAX_SUM + 1) {
			dp[i][curSum] = dp[i - 1][curSum];
			int prevSum = curSum - coins[i - 1];
			if (prevSum >= 0 && dp[i - 1][prevSum]) {
				dp[i][curSum] = true;
			}
		}
	}
	vi ans;
	forab (sum, 1, MAX_SUM + 1) {
		if (dp[n][sum])ans.pb(sum);
	}
	cout << sz(ans) << ln;
	for (int sum : ans) 
    cout << sum << " ";
	cout << ln;
  return 0;
}
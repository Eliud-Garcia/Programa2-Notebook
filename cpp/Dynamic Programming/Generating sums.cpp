
/* cantidad de formas para hacer 
la suma x usando las monedas dadas */
const int MAX_N = 100;
const int MAX_SUM = 1e6 + 1;
const int MOD = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }
    /*
    para formas ordenadas
    2+2+5 == 2+5+2
    */
    vector<int> dp(x + 1);
    dp[0] = 1;
    for (int j = 0; j < n; ++j) {
        for (int i = c[j]; i <= x; ++i) {
            dp[i] = (dp[i - c[j]] + dp[i]) % MOD;
        }
    }
    cout << dp[x] << ln;
    /*
        sin importar el orden
        de las combinaciones
        2+2+5 != 2+5+2
    */
    vector<int> ways(x + 1);
    ways[0] = 1;
    for (int j = 0; j < n; ++j) {
        for (int i = c[j]; i <= x; ++i) {
            ways[i] = (ways[i - c[j]] + ways[i]) % M;
        }
    }
    cout << ways[x] << ln;
    return 0;
}

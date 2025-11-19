
ll dp[55][55];
 
ll nCk(int N, int K) {
    if (N < K) return 0;
    if (N == K) return 1;
    if (K == 1) return N;
    ll &res = dp[N][K];
    if (res != -1) return res;
    res = nCk(N - 1, K - 1) + nCk(N - 1, K);
    return res;
}

//iterativo
const int MAXB = 50;
ll cb[MAXB+1][MAXB+1];

void precomp() {
	cb[0][0] = 1;
	for (int i = 1; i <= MAXB; i++) {
		cb[i][0] = 1;
		for (int j = 1; j <= MAXB; j++) {
			cb[i][j] = cb[i-1][j-1] + cb[i-1][j];
		}
	}
}
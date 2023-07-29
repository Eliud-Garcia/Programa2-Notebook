



static final int N = 1000;

    static int dp[][] = new int[N][N];

    static int n;
    static int w[] = new int[N];
    static int f[] = new int[N];

    static void solve() throws IOException {

        n = en.nextInt();
        for (int i = 0; i < n; i++) w[i] = en.nextInt();
        for (int i = 0; i < n; i++) f[i] = en.nextInt();
        int m = en.nextInt();
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int p = 0; p <= m; p++) {
                dp[i][p] = dp[i + 1][p];
                if (p >= w[i]) {
                    dp[i][p] = max(ans, dp[i + 1][p - w[i]] + f[i]);
                }
            }
        }
        sa.write(dp[0][m] + "\n");

    }

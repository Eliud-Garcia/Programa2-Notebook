
    static int MAX = (int) 1e4;
    static Integer dp[][] = new Integer[MAX][MAX];

    static int go(int coins[], int idx, int cambio) {
        if (idx < 0 || cambio < 0) {
            return 1000;
        }


        //ya está calculado
        if (dp[idx][cambio] != null) {
            return dp[idx][cambio];
        }

        if (cambio == 0) {
            return 0;
        }

        if (idx == 0) {
            return dp[idx][cambio] = 1 + go(coins, idx, cambio - coins[idx]);
        }

        //usar la moneda actual                                             o  avanzar a la otra
        return dp[idx][cambio] = min(1 + go(coins, idx, cambio - coins[idx]), go(coins, idx - 1, cambio));

    }

    public static void main(String[] args) throws IOException {
        int n = nextInt(), cambio = nextInt();

        int monedas[] = new int[n];
        for (int i = 0; i < n; i++) {
            monedas[i] = nextInt();
        }

        sa.printf("%d\n", go(monedas, n - 1, cambio));
        sa.close();
    }

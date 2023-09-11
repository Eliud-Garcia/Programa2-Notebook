
    static int MAX = (int) 1e7 + 1;
    static Long dp[] = new Long[MAX];

    public static long fib(int n) {
        if (n == 0)
            return 0;

        if (n == 1) {
            return 1;
        }

        if (dp[n] != null) {
            return dp[n];
        }

        return dp[n] = fib(n - 1) + fib(n - 2);
    }

    public static void main(String[] args) throws IOException {
        System.out.println(fib(46));
        sa.close();
    }

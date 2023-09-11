
    static int MAX = (int) 1e5 + 1;
    static Integer dp[] = new Integer[MAX];

    public static int tribonacci(int n) {
        if (n == 2)
            return 1;
        if (n == 1)
            return 0;
        if (n == 0)
            return 0;

        if (dp[n] != null) {
            return dp[n];
        }

        dp[n] = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
        return dp[n];
    }

    public static void main(String[] args) throws IOException {
        System.out.println(tribonacci(5));
        sa.close();
    }

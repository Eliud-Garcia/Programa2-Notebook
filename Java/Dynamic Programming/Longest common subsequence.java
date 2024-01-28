
    //Longest common subsequence
    /*
     * example:
     *  a = bd
     *  b = abcd
     *  LCS = bd
     *  ans = 2
     */
    static String a, b;
    static int n, m;
    static int dp[][];

    //recursive
    static int go(int i, int j){
        if(i >= n || j >= m){
            return 0;
        }
        if(a.charAt(i) == b.charAt(j)){
            return  dp[i][j] = 1 + go(i + 1, j + 1);
        }
        return dp[i][j] = max(go(i + 1, j), go(i, j + 1));
    }

    public static void main(String[] args){
        a = next();
        b = next();
        n = a.length();
        m = b.length();
        dp = new int[n][m];
        sa.print(go(0, 0)+"\n");
        //podemos reconstruir el LCS con
        //una matriz de parent[n][m][2];
        //parent[n][m][i] = i;
        //parent[n][m][j] = j;
        sa.close();
    }





//return the number of ways possible to travel 
//from the top-left corner of the grid to the bottom-right corner.

    static int N = 1000;
    static int MOD =(int) 1e9+7;
 
    static Long dp[][] = new Long[N][N];

    static long countPaths(int r, int c, char grid[][]) {
        // posicion no valida
        if (r >= grid.length || c >= grid[0].length) {
            return 0;
        }

        // si hay una pared
        if (grid[r][c] == '*') {
            return 0;
        }

        // si ya lo teniamos calculado
        if (dp[r][c] != null) {
            return dp[r][c];
        }

        // hemos encontrado un camino
        if (r == grid.length - 1 && c == grid[0].length - 1) {
            return 1;
        }

        // abajo = r+1, c
        // derecha = r, c+1
         dp[r][c] = countPaths(r + 1, c, grid) + countPaths(r, c + 1, grid);
         dp[r][c]%=MOD; //en caso de usar MOD
        return dp[r][c] ;
    }

    public static void main(String[] args) throws IOException {
        int n = en.nextInt();
        char grid[] [] = new char[n][n];
        for(int i = 0; i< n; i++){
            String line = en.next();
            for(int j = 0; j< line.length(); j++){
                grid[i][j] = line.charAt(j);
            }
        }
        sa.println(countPaths(0, 0, grid));
        sa.close();
    }
    
    
    //maxima suma del camino desde la primera casilla hasta la ultima
    //solo se puede mover hacia abajo y la derecha

    static Integer dp[][] = new Integer[1000][1000];

    public static int maxPathSum(int r, int c, int grid[][]) {
        if (r == grid.length || c == grid[0].length) {
            return Integer.MIN_VALUE;
        }

        //ya está calculado
        if (dp[r][c] != null) {
            return dp[r][c];
        }

        //llegamos a la ultima casilla
        if (r == grid.length - 1 && c == grid[0].length - 1) {
            return grid[r][c];
        }

        // dp[r][c] = posActual + max(abajo, derecha);
        return dp[r][c] = grid[r][c] + max(maxPathSum(r + 1, c, grid), maxPathSum(r, c + 1, grid));

    }

    public static void main(String[] args) throws IOException {

        int grid[][] = {
           {1, 3, 12},
           {5, 1, 1},
           {3, 6, 1},
        };

        sa.println(maxPathSum(0, 0, grid));
        sa.close();
    }

//para 4 direcciones
//up, right, down, left
static int dx[] = { -1, 0, 1, 0 };
static int dy[] = { 0, 1, 0, -1 };
// para 8 direcciones
static int dx8[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
static int dy8[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
static int grid[][];
static boolean visited[][];
static int curSize = 0;
static int n, m;

static void floodfill(int r, int c, int color) {
    if (r < 0 || r >= n || c < 0 || c >= m) return;
    if (grid[r][c] != color) return;
    if (visited[r][c]) return;
    visited[r][c] = true;
    curSize++;
    for (int i = 0; i < 4; i++) {
        floodfill(r + dx[i], c + dy[i], color);
    }
}

public static void main(String[] args) throws IOException {
    n = nextInt();
    m = nextInt();
    grid = new int[n][m];
    visited = new boolean[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = nextInt();
        }
    }
    //ejemplo, usando flood fill para contar islas
    int numberIslands = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j]==1) {
                curSize = 0;
                numberIslands++;
                floodfill(i, j, grid[i][j]);
            }
        }
    }
    sa.println(numberIslands);
    sa.close();
}
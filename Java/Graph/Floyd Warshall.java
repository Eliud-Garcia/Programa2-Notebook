static int n, m, q;
static long INF = Long.MAX_VALUE/10;
public static void main(String[] args) {
    // O(V^3)
    // Floyd Warshall
    n = nextInt();
    m = nextInt();
    q = nextInt();
    long g[][] = new long[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            g[i][j] = g[j][i] = INF;
        }
    }
    int a, b;
    long w;
    for (int i = 0; i < m; i++) {
        a = nextInt();
        b = nextInt();
        w = nextLong();
        a--; b--;
        g[a][b] = g[b][a] = min(g[a][b],w);
    }
    for(int k = 0; k < n ; k++){
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        a = nextInt();
        b = nextInt();
        a--; b--;
        sa.println(g[a][b] == INF? -1 : g[a][b]);
    }
    sa.close();
}
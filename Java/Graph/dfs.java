

    static boolean vis[];
    static ArrayList<Integer> adj[];
    static int dis[];

    /*
     * verificar conectividad
     * detectar ciclos
     */

    static void dfs(int node) {
        vis[node] = true;
        for (int next : adj[node]) {
            if (!vis[next]) {
                dfs(next);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        int n = 5;
        int m = 4;
        adj = new ArrayList[n + 1];
        vis = new boolean[n + 1];

        //inicializar grafo
        for (int i = 0; i <n+1; i++){
            adj[i] = new ArrayList<>();
        }

        adj[1].add(2);
        adj[2].add(5);
        adj[2].add(3);
        adj[3].add(4);

        dfs(1);

        sa.close();
    }

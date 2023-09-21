
    static boolean vis[];
    static ArrayList<Integer> adj[];

    static void dfs(int node) {
        vis[node] = true;
        for (int next : adj[node]) {
            if (!vis[next]) {
                dfs(next);
            }
        }
    }

    static void bfs(int node) {
        Queue<Integer> q = new ArrayDeque<>();
        q.add(node);
        while (!q.isEmpty()) {
            int cur = q.remove();
            if (!vis[cur]) {
                vis[cur] = true;
                for (int next : adj[cur]) {
                    q.add(next);
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        int n = 5;
        int m = 4;
        adj = new ArrayList[n + 1];
        vis = new boolean[n + 1];

        //inicializar grafo
        for (int i = 0, j = n ; i <=j; i++, j--){
            adj[i] = new ArrayList<>();
            adj[j] = new ArrayList<>();
        }

        adj[1].add(2);
        adj[2].add(5);
        adj[2].add(3);
        adj[3].add(4);

        dfs(1);

        sa.close();
    }

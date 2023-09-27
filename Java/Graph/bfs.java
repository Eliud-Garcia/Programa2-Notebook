
    //Breadth-first search

    static List<Integer> graph[];
    static boolean vis[];
    static int parent[];
    static int dis[];

    static void bfs(int node) {
        Queue<Integer> q = new LinkedList<>();
        q.add(node);
        vis[node] = true;
        parent[node] = -1;
        while (!q.isEmpty()) {
            int v = q.remove();
            // sa.println("Nodo "+v+" a distancia "+dis[v]);
            for (int u : graph[v]) {
                if (!vis[u]) {
                    vis[u] = true;
                    q.add(u);
                    dis[u] = dis[v] + 1;
                    parent[u] = v;
                    // sa.println("padre "+u+" = "+parent[u]);
                }
            }
        }
    }

    // unweighted graph.
    static void getShortestPath(int src, int dest) {
        if (!vis[dest]) {
            sa.println("No path!");
        } else {
            ArrayList<Integer> path = new ArrayList<>();
            for (src = dest; src != -1; src = parent[src])
                path.add(src);
            for (int i = path.size() - 1; i >= 0; i--) 
                sa.print(i != 0 ? path.get(i) + " " : path.get(i) + "\n");
            
        }
    }

    public static void main(String[] args) throws IOException {
        int n = nextInt();
        int m = nextInt();

        graph = new List[n + 1];
        vis = new boolean[n + 1];
        parent = new int[n + 1];
        dis = new int[n + 1];

        for (int i = 0; i < n + 1; i++) {
            graph[i] = new ArrayList<>();
        }
        int a, b = 0;

        while (m-- > 0) {
            a = nextInt();
            b = nextInt();
            graph[a].add(b);
            graph[b].add(a);
        }

        int src = 0;
        int dest = 4;
        bfs(src);
        getShortestPath(src, dest);

        sa.close();
    }

    /*
    
      5 5
      0 1
      0 3
      1 2
      3 2
      2 4
    
     */

static void bfs(ArrayList<Edge> graph[], boolean vis[], int start) {
        StringBuilder path = new StringBuilder();

        Queue<Integer> q = new LinkedList<>();
        q.add(start);

        while (!q.isEmpty()) {
            int cur = q.remove();
            if (vis[cur] == false) {
                path.append(cur).append(' ');
                vis[cur] = true;
                for (int i = 0; i < graph[cur].size(); i++) {
                    Edge e = graph[cur].get(i);
                    q.add(e.dest);
                }
            }
        }
        System.out.println(path);
    }


    static void dfs(ArrayList<Edge> graph[], int cur, boolean vis[]) {
        System.out.print(cur+" ");
        vis[cur] = true;
        for (int i = 0; i < graph[cur].size(); i++) {
            Edge e = graph[cur].get(i);
            if (!vis[e.dest]) {
                dfs(graph, e.dest, vis);
            }
        }
    }

    static void solve() throws IOException {
        int vertex = 7;
        ArrayList<Edge> graph[] = new ArrayList[vertex];
        for (int i = 0; i < graph.length; i++) {
            graph[i] = new ArrayList<Edge>();
        }

        graph[0].add(new Edge(0, 1));
        graph[0].add(new Edge(0, 2));
        graph[1].add(new Edge(1, 0));
        graph[1].add(new Edge(1, 3));
        graph[2].add(new Edge(2, 0));
        graph[2].add(new Edge(2, 4));
        graph[3].add(new Edge(3, 1));
        graph[3].add(new Edge(3, 4));
        graph[3].add(new Edge(3, 5));
        graph[4].add(new Edge(4, 2));
        graph[4].add(new Edge(4, 3));
        graph[4].add(new Edge(4, 5));
        graph[5].add(new Edge(5, 3));
        graph[5].add(new Edge(5, 4));
        graph[5].add(new Edge(5, 6));
        graph[6].add(new Edge(6, 5));

        boolean vis[] = new boolean[vertex];
        /*for (int i = 0; i < vertex; i++) {
            if (!vis[i]) {
                bfs(graph, vis, i);
            }
        }*/
        for (int i = 0; i < vertex; i++) {
            if(!vis[i]){
                dfs(graph, i, vis);
            }
        }

    }
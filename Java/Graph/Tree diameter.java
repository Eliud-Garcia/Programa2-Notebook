
    static List<Integer> tree[];
    static boolean vis[];
    static int dis[];
    static int n, m;
    static int nodoLejano, maxDis;

    static void bfs(int src) {
        vis = new boolean[n + 1];
        dis = new int[n + 1];
        
        Queue<Integer>q = new ArrayDeque<>();
        vis[src] = true;
        nodoLejano = src;
        q.add(src);
        while(!q.isEmpty()){
            int node = q.remove();
            if(dis[node] > maxDis){
                nodoLejano = node;
                maxDis = dis[node];
            }
            for (int next : tree[node]) {
                if(!vis[next]){
                    vis[next] = true;
                    dis[next] = dis[node] + dis[next] + 1;
                    q.add(next);
                }
            }
        }

    }

    public static void main(String[] args) throws IOException {
        n = nextInt();
        tree = new List[n + 1];
        vis = new boolean[n + 1];
        dis = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            tree[i] = new ArrayList<>();
        }
        int a, b;
        for (int i = 0; i < n - 1; i++) {
            a = nextInt();
            b = nextInt();
            tree[a].add(b);
            tree[b].add(a);
        }
        maxDis = 0;
        bfs(1);
        bfs(nodoLejano);
        sa.println(maxDis); // diameter

        sa.close();
    }

//Bellman Ford
//weighted directed graph
// O(m*n)
static class Edge{
    int u, v;
    long w;
    Edge(int a, int b, int ww){
        u = a;
        v = b;
        w = ww;
    }
}
static int n, m;
static long INF = Long.MAX_VALUE/22;
static List<Edge> edges = new ArrayList<>();
//negative cycle
static List<Integer> bellmanFord(int src, int n){
    long dis[] = new long[n];
    int parent[] = new int[n];
    Arrays.fill(dis, INF);
    Arrays.fill(parent, -1);
    int x = 0;
    for (int i = 0; i < n; i++) {
        x = -1;
        for (Edge e : edges) {
            if(dis[e.u] < INF){
                if (dis[e.v] > dis[e.u] + e.w) {
                    dis[e.v] = max(-INF, dis[e.u] + e.w);
                    parent[e.v] = e.u;
                    x = e.v;
                }
            }
        }
    }
    List<Integer>path = new ArrayList<>();
    if(x == -1){
        //No negative cycle from src
        return path;
    }else{
        int y = x;
        for (int i = 0; i < n; ++i)
            y = parent[y];

        for (int cur = y;; cur = parent[cur]) {
            path.add(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        Collections.reverse(path);
        return path;
    }
}

//shortest paths from vertex (src) to every other vertex.
static List<Integer> bellmanFord1(int src, int dest, int n){
    long dis[] = new long[n];
    int parent[] = new int[n];
    Arrays.fill(dis, INF);
    Arrays.fill(parent, -1);
    for (;;) {
        boolean any = false;
        for (Edge e : edges) {
            if(dis[e.u] < INF){
                if (dis[e.v] > dis[e.u] + e.w) {
                    dis[e.v] = dis[e.u] + e.w;
                    parent[e.v] = e.u;
                    any = true;
                }
            }
        }
        if(!any){
            break;
        }
    }
    List<Integer>path = new ArrayList<>();
    if (dis[dest] == INF){
        //No Path from src to dest
        return path;
    }else {
        for (int cur = dest; cur != -1; cur = parent[cur])
            path.add(cur);
        Collections.reverse(path);
        //Path from src to dest
        /*
        for (int u : path)
            cout << u << ' ';
        */
        return path;
    }
}
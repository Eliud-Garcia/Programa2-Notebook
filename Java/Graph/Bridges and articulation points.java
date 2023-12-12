
    //Tarjan's Algorithm
    //Finding bridges in a graph in O(N + M)
    //Undirected graph.
    
    static List<Integer> g[];
    static int tin[];
    static int low[];
    static int timer = 0;
    //static List<edge> bridges;
    //static List<Integer> articPoints;
    static void dfsBr(int node, int p){
        tin[node] = low[node] = timer++;
        for (int next : g[node]) {
            if(next == p) continue;
            if(tin[next] == -1){
                dfsBr(next, node);
                low[node] = min(low[node], low[next]);
                if(tin[node] < low[next]){
                    //is bridge (a, b)
                    //bridges.add(new edge(node, next));
                }
            }else{
                low[node] = min(low[node], tin[next]);
            }
        }
    }

    //articulation points
    static void dfsAP(int node, int p){
        tin[node] = low[node] = timer++;
        int children = 0;
        for (int next : g[node]) {
            if(next == p) continue;
            if(tin[next] == -1){
                children++;
                dfsAP(next, node);
                low[node] = min(low[node], low[next]);
                if(tin[node] <= low[next] && p!= - 1){
                    // node is a articulation point
                    //articPoints.add(node);
                }
            }else{
                low[node] = min(low[node], tin[next]);
            }
        }
        if(p == -1 && children > 1){
            sa.print(node+"\n");
        }
    }
    
    static int n, m;
    public static void main(String[] args) {
        n = nextInt();
        m = nextInt();

        g = new List[n + 1];
        tin = new int[n + 1];
        low = new int[n + 1];
        //bridges = new ArrayList<>();
        Arrays.setAll(g, i -> new ArrayList<>());
        Arrays.fill(tin, -1);
        
        int a, b;
        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            g[a].add(b);
            g[b].add(a);
        }

        //find bridges
        for (int i = 1; i <= n; i++) {
            if(tin[i] == -1){
                dfsBr(i, -1);
            }
        }
        
        Arrays.fill(tin, -1);
        //find articulation points
        for (int i = 1; i <= n; i++) {
            if(tin[i] == -1){
                dfsAP(i, -1);
            }
        }
        sa.close();
    }

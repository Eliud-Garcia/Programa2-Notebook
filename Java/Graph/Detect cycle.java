

    // undirected graph
    static List<Integer> graph[];
    static boolean vis[];
    static int parent[];
    static int n, m;
    static int star_cycle = -1, end_cycle = -1;


    static boolean dfs(int node, int par){
        vis[node] = true;
        parent[node] = par;

        for (int next : graph[node]) {
            if(next == par) continue;
            if(vis[next]){
                star_cycle = next;
                end_cycle = node;
                return true;
            }
            if(!vis[next] && dfs(next, node)){
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        n = nextInt();
        m = nextInt();

        graph = new List[n + 1];
        vis = new boolean[n + 1];
        parent = new int[n + 1];

        for (int i = 0; i < n + 1; i++) 
            graph[i] = new ArrayList<>();

        int a , b;
        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            graph[a].add(b);
            graph[b].add(a);
        }

        for (int i = 1; i < n + 1; i++) {
            if(!vis[i] && dfs(i, -1)){
                break;
            }
        }

        if(star_cycle == -1){
            sa.println("No hay ciclo");
        }else{
            sa.println("si hay ciclo");
            ArrayList<Integer> path = new ArrayList<>();
            path.add(end_cycle);
            for (int i = end_cycle; i != star_cycle; i=parent[i]) {
                path.add(parent[i]);
            }
            path.add(end_cycle);
            
            sa.println(path.size());
            for (int k : path) {
                sa.print(k+" ");
            }

        }

        sa.close();
    }


    //########################################################################################

    // directed graph

    
    static List<Integer> graph[];
    static int parent[];
    static int color[];
    static int n, m;
    static int cycle_start = -1, cycle_end = -1;

    static boolean dfs(int node) {
        color[node] = 1;
        for (int next : graph[node]) {
            if (color[next] == 0) {
                parent[next] = node;
                if (dfs(next)) {
                    return true;
                }
            } else if (color[next] == 1) {
                cycle_end = node;
                cycle_start = next;
                return true;
            }
        }
        color[node] = 2;
        return false;
    }

    public static void main(String[] args) throws IOException {
        n = nextInt();
        m = nextInt();

        graph = new List[n + 1];
        parent = new int[n + 1];
        color = new int[n + 1];

        for (int i = 0; i < n + 1; i++) {
            graph[i] = new ArrayList<>();
        }

        int a, b;
        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            graph[a].add(b);
        }

        for (int i = 1; i < n + 1; i++) {
            if (color[i] == 0 && dfs(i)) {
                break;
            }
        }
        
        if (cycle_start == -1) {
            sa.println("No hay ciclo");
        } else {
            sa.println("Si hay ciclo");
        }

        sa.close();
    }

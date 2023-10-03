

    static List<Integer> graph[];
    static boolean vis[];
    static int parent[];
    static int dis[];
    static int ans[];
    static int n, m;
    static int star_cycle, end_cycle;
    static boolean found;


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

        boolean visitAll = false;
        for (int i = 1; i < n + 1; i++) {
            if(!vis[i] && dfs(i, -1)){
                visitAll = true;
                break;
            }
        }

        if(!visitAll){
            //No hay ciclo
            sa.println("IMPOSSIBLE");
        }else{
            //si hay ciclo
            ArrayList<Integer> path = new ArrayList<>();
            path.add(end_cycle);
            for (int i = end_cycle; i != star_cycle; i=parent[i]) {
                path.add(parent[i]);
            }
            path.add(end_cycle);

            //sa.println("inicia en "+end_cycle+" termina en "+star_cycle);
            
            sa.println(path.size());
            for (int k : path) {
                sa.print(k+" ");
            }

        }

        sa.close();
    }

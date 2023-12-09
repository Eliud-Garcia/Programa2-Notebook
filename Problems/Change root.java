

    // cada nodo se elige como raiz y dice 
    // cuantos nodos estan pintados en su subArbol
    // https://codeforces.com/gym/102348/problem/B
    static int n, k;
    static List<Integer> tree[];
    static long sum[];
    static boolean colored[];
    static List<Integer> ans;

    static void dfs(int node, int p){
        if(colored[node]) sum[node]++;
        for (int next : tree[node]) {
            if(next == p) continue;
            dfs(next, node);
            sum[node]+=sum[next];
        }
    }

    static void change_root(int root, int p){
        boolean ok = !colored[root];
        for (int child : tree[root]) {
            ok &= (sum[child] > 0);
        }
        if(ok) ans.add(root);
        for (int next : tree[root]) {
            if(next == p) continue;
            long prevRoot = sum[root];
            long prevNext = sum[next];
            sum[root]-=sum[next];
            sum[next] = prevRoot;
            change_root(next, root);
            sum[root] = prevRoot;
            sum[next] = prevNext;
        }
    }

    public static void main(String[] args) {
        n = nextInt();
        k = nextInt();
        tree = new List[n + 1];
        sum = new long[n + 1];
        colored = new boolean[n + 1];
        ans = new ArrayList<>();
        Arrays.setAll(tree, i -> new ArrayList<>());
        for (int i = 0; i < k; i++) {
            colored[nextInt()] = true;
        }
        int a, b;
        for (int i = 0; i < n - 1; i++) {
            a = nextInt();
            b = nextInt();
            tree[a].add(b);
            tree[b].add(a);
        }

        dfs(1, 1);
        change_root(1, 1);
        sa.print(ans.size()+"\n");
        Collections.sort(ans);
        for (int i : ans) {
            sa.print(i+" ");
        }
        sa.close();
    }

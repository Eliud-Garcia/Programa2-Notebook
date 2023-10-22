
    static final long INF = Long.MAX_VALUE;
    static List<edge> g[];
    static double dis[];
    static int par[];
    static boolean vis[];
    static int n, m, k;

    static class edge {
        int v;
        double w;
        double vel;

        edge(int node, double weight, double speed) {
            v = node;
            w = weight;
            vel = speed;
        }
    }

    // dijkstra(int source, int des)
    static boolean dijkstra(int s, double exc) {

        Comparator<edge> cmp = new Comparator<edge>() {
            @Override
            public int compare(edge a, edge b) {
                return Double.compare(a.w, b.w);
            }
        };
        PriorityQueue<edge> pq = new PriorityQueue<>(cmp);

        Arrays.fill(dis, INF);

        // new edge(node, weight);
        pq.add(new edge(s, 0, 0));

        dis[s] = 0;
        par[s] = -1;

        while (!pq.isEmpty()) {
            edge x = pq.poll();
            int u = x.v;

            vis[u] = true;

            for (edge next : g[u]) {
                int v = next.v;
                double w = next.w;
                double vel = next.vel;

                w = w / (vel + exc);

                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    pq.add(new edge(v, dis[v], vel));
                    par[v] = u;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        n = nextInt();
        m = nextInt();
        k = nextInt();

        g = new ArrayList[n + 1];
        dis = new double[n + 1];
        par = new int[n + 1];
        vis = new boolean[n + 1];

        for (int i = 0; i <= n; i++) {
            g[i] = new ArrayList<>();
        }

        int a, b;
        double w, speed;

        for (int i = 0; i < m; i++) {
            a = nextInt();
            b = nextInt();
            w = nextDouble();
            speed = nextDouble();

            g[a].add(new edge(b, w, speed));
            g[b].add(new edge(a, w, speed));
        }

        dijkstra(1, 0);
        if (dis[n] <= k) {
            sa.println(0);
        } else {

            //buscando llegar a tiempo k 
            //tratando de exceder lo minimo posible
            //los limites de velocidad
            double l = 0, r = 1e9, mid = -1;
            int it = 50;
            while (it-- > 0) {
                mid = l + (r - l) / 2;
                dijkstra(1, mid);

                if (dis[n] > k) {
                    l = mid;
                } else {
                    r = mid;
                }
            }

            sa.printf("%.7f", mid);
        }

        sa.close();
    }

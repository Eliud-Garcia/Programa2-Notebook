import java.util.*;

public class Dijkstra {

    static class Edge {
        int from, to, weight;

        public Edge(int from, int to, int weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }

        @Override
        public String toString() {
            return "from : " + from + " ,to: " + to + " weight: " + weight;
        }
    }

    static class Vertex {
        int nodeId;
        long cost; // can overflow int

        public Vertex(int nodeId, long cost) {
            this.nodeId = nodeId;
            this.cost = cost;
        }
    }

    static private LinkedList<Vertex>[] getGraphFromEdges(Edge[] edges, int n) {
        LinkedList<Vertex>[] graph = new LinkedList[n + 1];
        for (int i = 1; i <= n; i++) {
            graph[i] = new LinkedList<Vertex>();
        }
        for (Edge edge : edges) {
            graph[edge.from].add(new Vertex(edge.to, edge.weight));
        }
        return graph;
    }

    static private LinkedList<Integer> getShortestPath(Edge[] edges, int rootNode, int n) {
        boolean fronteer[] = new boolean[n + 1];// assuming base 1 index
        int path[] = new int[n + 1];
        Arrays.fill(path, -1);
        long distance[] = new long[n + 1];
        Arrays.fill(distance, Long.MAX_VALUE / 10);
        PriorityQueue<Vertex> pQueue = new PriorityQueue<Vertex>(n, (a, b) -> Long.compare(a.cost, b.cost));
        fronteer[rootNode] = true;
        distance[rootNode] = 0;
        LinkedList<Vertex>[] graph = getGraphFromEdges(edges, n);
        pQueue.add(new Vertex(1, 0));
        while (!pQueue.isEmpty()) {
            Vertex u = (Vertex) pQueue.poll();
            for (Vertex v : graph[u.nodeId]) {
                if (!fronteer[v.nodeId] && distance[u.nodeId] + v.cost < distance[v.nodeId]) {
                    distance[v.nodeId] = distance[u.nodeId] + v.cost;
                    path[v.nodeId] = u.nodeId;
                    pQueue.add(new Vertex(v.nodeId, distance[v.nodeId]));
                }
            }
            fronteer[u.nodeId] = true;// add it to frounter
        }
        LinkedList<Integer> shortestPath = new LinkedList<>();
        shortestPath.add(n);
        int idx = n;
        while (path[idx] != -1) {
            shortestPath.addFirst(path[idx]);
            idx = path[idx];
        }
        return shortestPath;
    }

    /*
     * Ejemplo de uso
     * 
     * https://codeforces.com/contest/20/problem/C
     * C. Dijkstra?
     */
    
    public static void main(String []args) {
        Scanner en = new Scanner(System.in);
        int n = en.nextInt(), m = en.nextInt();
        Edge edges[] = new Edge[2 * m];
        for (int i = 0; i < m; i++) {
            int inicio = en.nextInt(), fin = en.nextInt(), peso = en.nextInt();
            edges[i] = new Edge(inicio, fin, peso);
            edges[i + m] = new Edge(fin, inicio, peso);
        }

        LinkedList<Integer> path = getShortestPath(edges, 1, n);
        if (path.isEmpty() || path.getFirst() != 1)
            System.out.println(-1);
        else {
            StringBuilder sb = new StringBuilder();
            for (int i : path) {
                sb.append(i);
                sb.append(' ');
            }
            System.out.println(sb);
        }
    }
}
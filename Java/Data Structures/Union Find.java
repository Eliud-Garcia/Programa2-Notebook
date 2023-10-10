


    static class UnionFind {
        int parent[];
        int size[];
        int maxi[];
        int mini[];

        UnionFind(int n) {
            n++;
            parent = new int[n];
            size = new int[n];
            maxi = new int[n];
            mini = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                size[i] = 1;
                maxi[i] = i;
                mini[i] = i;
            }
        }

        //Path compression optimization
        int find(int a) {
            return parent[a] = (parent[a] == a) ? a : find(parent[a]);
        }

        //Union by size
        void union(int x, int y) {
            int a = find(x);
            int b = find(y);
            if (a == b) return;

            if (size[a] > size[b]) {
                parent[b] = a;
                mini[a] = min(mini[a], mini[b]);
                maxi[a] = max(maxi[a], maxi[b]);
                size[a] += size[b];
            } else {
                parent[a] = b;
                mini[b] = min(mini[b], mini[a]);
                maxi[b] = max(maxi[b], maxi[a]);
                size[b] += size[a];
            }
        }

        boolean isSame(int a, int b) {
            return find(a) == find(b);
        }

    }

struct UnionFind {
    vi parent;
    vi size;
    vi maxi;
    vi mini;

    UnionFind(int n){
        n++;
        parent = vi(n);
        size = vi(n);
        maxi = vi(n);
        mini = vi(n);
        forn(i, n){
            parent[i] = i;
            size[i] = 1;
            maxi[i] = i;
            mini[i] = i;
        }
    }
    // Path compression optimization
    int find(int a){
        return parent[a] = (parent[a] == a) ? a : find(parent[a]);
    }
    // Union by size
    void unionF(int x, int y){
        int a = find(x);
        int b = find(y);
        if (a == b)return;

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

    bool isSame(int a, int b){
        return find(a) == find(b);
    }
};

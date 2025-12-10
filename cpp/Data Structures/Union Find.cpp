
const int MAXN = 2e5 + 5;
struct dsu{
    int n;
    int p[MAXN], tam[MAXN];
    ll sum[MAXN], lazy[MAXN];
    vector<int> child[MAXN];
    
    void init(int nx){
        n = nx;
        for(int i = 0; i <= n; i++){
            p[i] = i;
            tam[i] = 1;
            sum[i] = 0;
            lazy[i] = 0;
            child[i].push_back(i);
        }
    }

    int find(int x){
        if(x == p[x]) return x;
        return p[x] = find(p[x]);
    }

    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return;
        if(tam[a] < tam[b]) swap(a, b);
        tam[a] += tam[b];
        p[b] = a;

        for(int i: child[b]){
            sum[i] += lazy[b] - lazy[a];
            child[a].push_back(i);
        }
        lazy[b] = 0;
    }
    
    void add(int x, int s){
        lazy[find(x)] += s;
    }
    
    int get(int x){
        return sum[x] + lazy[find(x)];
    }
};
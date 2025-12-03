
int get_idx(int i){
    //es el indice donde inicia el
    //bloque en el que cae i
    return (i / S) * S;
}

int n, q;
const int MAXN = 1e5;
const int S = 317; //sqrt(n)
const int B = MAXN / S + 1;

int a[MAXN];
vector<int> blk[B];
int sum[B];

//agrega x a todos en el rango [l, r]
void add(int l, int r, int x){
    l--, r--;
    int i = l;
    while(i <= r){
        if(i % S == 0 && i + S < r){
            sum[i / S] += x;
            i += S;
        }else{
            auto& b = blk[i / S];
            auto it = lower_bound(all(b), a[i]);
            b.erase(it);

            a[i] += x;
            b.insert(lower_bound(all(b), a[i]), a[i]);
            i++;
        }
    }
}

//valida si x está en el rango l, r
int qry(int l, int r, int x){
    l--, r--;
    int ans = 0;
    int i = l;
    while(i <= r){
        if(i % S == 0 && i + S < r){
            auto& b = blk[i / S];
            int to_search = x - sum[i / S];
            auto it = lower_bound(all(b), to_search);
            if(it != b.end() && *it == to_search){
                ans++;
            }
            i += S;
        }else{
            ans += (a[i] + sum[i / S] == x);
            i++;
        }
    }
    return ans;
}

int main() {
    cin >> n >> q;
    forn(i, n) cin >> a[i];

    int mx = 0;
    forn(i, n){
        blk[i / S].push_back(a[i]);
        sum[i / S] = 0;
        mx = max(mx, i / S);
    }
    for(int i = 0; i <= mx; i++) {
        sort(all(blk[i]));
    }
    while(q--){
        char c;
        int l, r, x;
        cin >> c;
        cin >> l >> r >> x;
        if(c == '+'){
            add(l, r, x);
        }else{
            int ans = qry(l, r, x);
            cout << (ans ? "YES" : "NO") << ln;
        }
    }
    return 0;
}

//n = 1e5
//q = 1e5
//time = 3562 ms
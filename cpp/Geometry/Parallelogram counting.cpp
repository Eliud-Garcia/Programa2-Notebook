
/*
dado un conjunto de puntos, contar
la cantidad de paralelogramas que se pueden formar
*/
struct pair_hash {
    size_t operator()(const pair<ll, ll>& p) const {
        size_t h1 = hash<ll>{}(p.first);
        size_t h2 = hash<ll>{}(p.second);
        return h1 ^ (h2 * 2654435761ULL + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

int main() {
    int n; cin >> n;
    vector<array<ll, 2>> a;
    for(int i = 0; i < n; i++){
        ll x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }

    unordered_map<pair<ll, ll>, int, pair_hash> mp;
    mp.reserve(n * (n - 1) / 2);
    
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            //contar puntos medios (x1 + x2, y1 + y2)
            mp[{a[i][0] + a[j][0], a[i][1] + a[j][1]}]++;
            //si comparten un punto medio, forman un paralelograma
        }
    }
    ll ans = 0;
    for(auto [d, q] : mp){
        ans += (q * (q - 1) / 2);
    }
    printf("%lld\n", ans);
    return 0;
}
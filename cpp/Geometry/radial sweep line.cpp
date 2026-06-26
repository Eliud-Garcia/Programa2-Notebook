
const double EPS = 1e-11;
const double PI = acos(-1.0);

int main() {
    int t; cin >> t;
    for(int tt = 0; tt < t; tt++){
        int n, m;
        double z;
        cin >> n >> m >> z;

        double R = z / 2;

        vector<pair<double, int>> events;
        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            double alpha = atan2(y, x);
            double d = hypot(x, y);//distancia
            if(alpha < 0){
                alpha += 2 * PI;
            }

            double delta = 0;
            if(d <= R + EPS){
                delta = PI / 2;
            }else{
                delta = asin(R / d);
            }

            double left = alpha - delta;
            double right = alpha + delta;

            while (left < 0) {
                left += 2 * PI;
                right += 2 * PI;
            }
            while (left >= 2 * PI) {
                left -= 2 * PI;
                right -= 2 * PI;
            }
            if (right >= 2 * PI) {
                //da la vuelta (se separa en 2 segmentos)
                events.push_back({left, 1});
                events.push_back({2 * PI, -1});
                events.push_back({0.0, 1});
                events.push_back({right - 2 * PI, -1});
            } else {
                events.push_back({left, 1});
                events.push_back({right, -1});
            }
        }
        auto cmp = [&](pair<double, int> a, pair<double, int> b){
            if(fabs(a.first - b.first) > EPS){
                return a.first < b.first;
            }
            return a.second > b.second;
        };
        sort(all(events), cmp);

        int total = 0;
        int mx = 0;
        for(auto [x, state] : events){
            total += state;
            mx = max(mx, total);
        }
        cout << (mx >= m ? "Yes" : "No") << ln;
    }
    return 0;
}
/*
un rayo sale desde (0, 0) y tiene z de ancho
el rayo solo apunta en una direccion
indicar la mayor cantidad de puntos que puede
abarcar el rayo en un disparo
*/

typedef long long T;
struct pt {
    T x, y;
    pt(T x_ = 0, T y_ = 0) : x(x_), y(y_) {
    }
    bool operator<(const pt p) const {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
    }
    pt operator-(const pt p) const {
        return pt(x - p.x, y - p.y);
    }
    T operator*(const pt p) const {
        return x * p.x + y * p.y;
    }
    T operator^(const pt p) const {
        return x * p.y - y * p.x;
    }
};
//https://cp-algorithms.com/geometry/convex-hull.html
int orientation(pt a, pt b, pt c) {
    T v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1;  // clockwise
    if (v > 0) return +1;  // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o > 0 || (include_collinear && o == 0);
}

vector<pt> convex_hull(vector<pt>& a, bool include_collinear = false) {
    if (sz(a) == 1) return a;
    sort(all(a));
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down, hull;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < sz(a); i++) {
        if (i == sz(a) - 1 || cw(p1, a[i], p2, include_collinear)) {
            while (sz(up) >= 2 && !cw(up[sz(up) - 2], up[sz(up) - 1], a[i], include_collinear))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == sz(a) - 1 || ccw(p1, a[i], p2, include_collinear)) {
            while (sz(down) >= 2 && !ccw(down[sz(down) - 2], down[sz(down) - 1], a[i], include_collinear))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    if (include_collinear && sz(up) == sz(a)) {
        reverse(a.begin(), a.end());
        return a;
    }
    for (int i = 0; i < sz(up); i++) hull.push_back(up[i]);
    for (int i = sz(down) - 2; i > 0; i--) hull.push_back(down[i]);
    return hull;
}

// calcula el angulo ABC usando los vectores BA y BC
// B es el vertice
double get_angle(pt A, pt B, pt C) {
    pt BA = B - A, BC = B - C;
    T dot = BA * BC;
    T cross = BA ^ BC;
    return atan2(abs(cross), dot);//angulo en radianes
}

const double PI = acos(-1.0);
double RAD_TO_DEG(double rad) {
    return rad * 180.0 / PI;
}

int main() {
    int t; cin >> t;
    for (int tt = 0; tt < t; tt++) {
        int n; cin >> n;
        vector<pt> pts(n);
        for (int i = 0; i < n; i++) {
            cin >> pts[i].x >> pts[i].y;
        }
        vector<pt> hull = convex_hull(pts);
        double min_angle = 1e9;
        if (sz(hull) < 3) {
            min_angle = 0.0;
        }else{
            for (int i = 0; i < sz(hull); i++) {
                int left = ((i - 1) + sz(hull)) % sz(hull);
                pt l = hull[left];
                pt c = hull[i];
                pt r = hull[(i + 1) % sz(hull)];
                double ang = get_angle(l, c, r);
                ang = RAD_TO_DEG(ang);
                min_angle = min(min_angle, ang);
            }
        }
        printf("Case %d: %.6lf\n", tt + 1, min_angle);
    }
    return 0;
}
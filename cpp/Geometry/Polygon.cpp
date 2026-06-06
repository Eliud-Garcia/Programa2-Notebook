// Traer el struct Point de Objects.cpp
struct Polygon {
    vector<Point> P;

    Polygon() {}
    Polygon(const vector<Point>& pts) : P(pts) {}

    int n() const { return sz(P); }

    void close() {
        if (P.empty()) return;
        if (!(P.front() == P.back())) P.push_back(P.front());
    }
    double area() const {
        double A = 0;
        for (int i = 0; i < n(); i++) {
            int j = (i + 1) % n();
            A += P[i].cross(P[j]);
        }
        return fabs(A) / 2.0;
    }
    double area2() const {
        double A = 0;
        for(int i = 0; i < n(); i++){
            A += P[i].cross(P[(i + 1) % sz(P)]);
        }
        return abs(A);
    }

    // Signed area (positive = CCW)
    double signedArea() const {
        double A = 0;
        for (int i = 0; i < n(); i++) {
            int j = (i + 1) % n();
            A += P[i].cross(P[j]);
        }
        return A / 2.0;
    }

    //clockwise (CW) if signed area < 0
    bool isCCW() const { return signedArea() > 0; }

    //determine if a point is inside, outside or on the border of the polygon
    //  0 -> out, 1 -> in, 2 -> on the border
    int containsPoint(const Point& q) const {
        bool inside = false;
        for (int i = 0, j = n() - 1; i < n(); j = i++) {
            const Point& a = P[i];
            const Point& b = P[j];

            if (fabs(orientation(a, b, q)) < EPS && 
                min(a.x, b.x) - EPS <= q.x && q.x <= max(a.x, b.x) + EPS &&
                min(a.y, b.y) - EPS <= q.y && q.y <= max(a.y, b.y) + EPS)
                return 2; // En el borde

            bool intersect = ((a.y > q.y) != (b.y > q.y)) &&
                             (q.x < (b.x - a.x) * (q.y - a.y) / (b.y - a.y + EPS) + a.x);
            if (intersect) inside = !inside;
        }
        return inside ? 1 : 0;
    }
    
    /*Para la cantidad de puntos 
    usar long long en Point y el metodo area2()*/
    //coordenadas (x, y) enteras en el borde del poligono
    ll puntosEnterosBordes(){
        ll bordes = 0;
        for(int i = 0; i < sz(P); i++){
            Point df = P[i] - P[(i + 1) % sz(P)];
            bordes += __gcd(abs(df.x), abs(df.y));
        }
        return bordes;
    }
    //coordenadas (x, y) enteras dentro del poligono
    ll puntosEnterosInternos(){
        ll bordes = puntosEnterosBordes();
        ll area_poly = area2();
        // area = pts_dentro + pts_borde / 2 - 1
        // area - pts_borde / 2 + 1 = pts_dentro
        return (area_poly - bordes) / 2LL + 1;
    }
};

// Convex Hull using Andrew's monotone chain algorithm
vector<Point> convexHull(vector<Point> pts) {
    int n = pts.size(), k = 0;
    if (n <= 1) return pts;

    sort(pts.begin(), pts.end());
    vector<Point> H(2 * n);

    //lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && orientation(H[k-2], H[k-1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }

    //upper hull
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && orientation(H[k-2], H[k-1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }

    H.resize(k - 1);
    return H;
}

// calculte the diameter of a convex polygon (the farthest pair of points)
double polygonDiameter(const vector<Point>& P) {
    int n = P.size();
    if (n == 1) return 0;
    if (n == 2) return dist(P[0], P[1]);

    double maxDist = 0;
    int j = 1;
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        while (fabs((P[ni] - P[i]).cross(P[(j + 1) % n] - P[i])) >
               fabs((P[ni] - P[i]).cross(P[j] - P[i])))
            j = (j + 1) % n;
        maxDist = max(maxDist, dist(P[i], P[j]));
    }
    return maxDist;
}




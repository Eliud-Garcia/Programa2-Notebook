// for use this structure, include Point_and_Segments.cpp
struct Polygon {
    vector<Point> P;

    Polygon() {}
    Polygon(const vector<Point>& pts) : P(pts) {}

    int n() const { return (int)P.size(); }

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Point> pts = {
        {0,0}, {1,2}, {2,1}, {4,4}, {0,4}, {3,0}
    };

    //Convex Hull
    vector<Point> hull = convexHull(pts);
    cout << "Convex Hull:\n";
    for (auto &p : hull) cout << "(" << p.x << "," << p.y << ") ";
    cout << "\n";

    Polygon poly(hull);
    cout << "Área: " << poly.area() << "\n";

    // poin in polygon test
    Point test(2, 2);
    int inside = poly.containsPoint(test);
    cout << "El punto (2,2) está: " 
         << (inside == 1 ? "Dentro" : inside == 2 ? "En el borde" : "Fuera") << "\n";

    cout << "Diámetro del polígono: " << polygonDiameter(hull) << "\n";
}



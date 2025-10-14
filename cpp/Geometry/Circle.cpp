//Require struct Point and functions (dot, cross, dist, perp, etc.)

// Vector perpendicular (rotado 90° CCW)
Point perp(const Point& a) {
    return Point(-a.y, a.x);
}

//Estructura de línea (útil para intersecciones)
struct Line {
    Point p;   // punto en la línea
    Point v;   // vector director

    Line() {}
    Line(Point _p, Point _v) : p(_p), v(_v) {}

    // Proyección de un punto sobre la línea
    Point proj(const Point& a) const {
        return p + v * ( (a - p).dot(v) / v.norm2() );
    }

    // Distancia cuadrada de un punto a la línea
    double sqDist(const Point& a) const {
        return ((a - p).cross(v) * (a - p).cross(v)) / v.norm2();
    }
};

//Circuncentro de un triángulo (pasa por A, B, C)
Point circumCenter(Point a, Point b, Point c) {
    b = b - a, c = c - a; // coordenadas relativas a A
    double d = cross(b, c);
    assert(fabs(d) > EPS); // no existe circunferencia si son colineales
    Point res = a + perp(b * c.norm2() - c * b.norm2()) * (0.5 / d);
    return res;
}

//Signo generalizado
template <typename T>
int sgn(T x) { return (x > 0) - (x < 0); }

//Intersección círculo-línea
// Devuelve:
//   0 → no toca
//   1 → tangente
//   2 → intersección en dos puntos
int circleLine(Point o, double r, Line l, pair<Point, Point>& out) {
    double h2 = r * r - l.sqDist(o);
    if (h2 < -EPS) return 0; // no intersecan

    Point p = l.proj(o);
    if (h2 < EPS) { // tangente
        out = {p, p};
        return 1;
    }
    Point h = l.v * (sqrt(h2) / l.v.norm());
    out = {p - h, p + h};
    return 2;
}

// Intersección entre dos círculos
// Devuelve 0, 1 o 2 dependiendo del número de intersecciones
int circleCircle(Point o1, double r1, Point o2, double r2, pair<Point, Point>& out) {
    Point d = o2 - o1;
    double dist2 = d.norm2();
    double distv = sqrt(dist2);

    if (distv < EPS) return 0; // concéntricos → sin puntos definidos

    double pd = (dist2 + r1 * r1 - r2 * r2) / (2 * distv); // distancia al punto base
    double h2 = r1 * r1 - pd * pd;
    if (h2 < -EPS) return 0; // no se cruzan

    Point base = o1 + d * (pd / distv);
    if (h2 < EPS) { // tangentes
        out = {base, base};
        return 1;
    }

    Point h = perp(d) * (sqrt(h2) / distv);
    out = {base - h, base + h};
    return 2;
}

// Tangentes comunes entre dos círculos
// inner = false → tangentes externas
// inner = true  → tangentes internas
// Devuelve 0, 1 o 2 pares de puntos (tangencias)
int tangents(Point o1, double r1, Point o2, double r2, bool inner, vector<pair<Point, Point>>& out) {
    if (inner) r2 = -r2;
    Point d = o2 - o1;
    double dr = r1 - r2;
    double d2 = d.norm2();
    if (d2 < EPS) return 0; // círculos concéntricos → sin tangentes
    double h2 = d2 - dr * dr;
    if (h2 < -EPS) return 0; // sin tangentes reales

    for (double sign : {-1.0, 1.0}) {
        Point v = (d * dr + perp(d) * sqrt(max(0.0, h2)) * sign) / d2;
        out.push_back({o1 + v * r1, o2 + v * r2});
    }

    return (h2 > EPS ? 2 : 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- Circuncentro ---
    Point A(0,0), B(4,0), C(0,3);
    Point O = circumCenter(A, B, C);
    cout << "Circuncentro: (" << O.x << ", " << O.y << ")\n";

    // --- Círculo-Línea ---
    Line l(Point(0,0), Point(1,1)); // y = x
    pair<Point,Point> inter;
    int t1 = circleLine(Point(2,0), 2.0, l, inter);
    cout << "Intersección círculo-línea: " << t1 << " puntos\n";
    if (t1) cout << "(" << inter.first.x << "," << inter.first.y << ") "
                 << "(" << inter.second.x << "," << inter.second.y << ")\n";

    // --- Círculo-Círculo ---
    pair<Point,Point> cc;
    int t2 = circleCircle(Point(0,0), 3, Point(4,0), 3, cc);
    cout << "Intersección círculo-círculo: " << t2 << " puntos\n";
    if (t2) cout << "(" << cc.first.x << "," << cc.first.y << ") "
                 << "(" << cc.second.x << "," << cc.second.y << ")\n";

    // --- Tangentes ---
    vector<pair<Point,Point>> tangs;
    int t3 = tangents(Point(0,0), 2, Point(6,0), 2, false, tangs);
    cout << "Tangentes externas: " << t3 << "\n";
    for (auto& p : tangs)
        cout << "T1(" << p.first.x << "," << p.first.y << ") "
             << "T2(" << p.second.x << "," << p.second.y << ")\n";

    return 0;
}

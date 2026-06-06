//PUNTO
const double EPS = 1e-9;
const double PI = acos(-1.0);

int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    bool operator<(const Point& p) const {
        if (sgn(x - p.x) != 0) return x < p.x;
        return y < p.y;
    }
    bool operator==(const Point& p) const {
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
    }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    double norm2() const { return x * x + y * y; }
    double norm() const { return sqrt(norm2()); }
    //rotate point by angle (in radians) around the origin
    Point rotate(double ang) const {
        double c = cos(ang), s = sin(ang);
        return Point(x * c - y * s, x * s + y * c);
    }
    //angle align with x axis
    double angle() const { return atan2(y, x); }
};

//calculete the distance between two points (distance eucludiana)
double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

// > 0 → giro antihorario
// < 0 → giro horario
// = 0 → colineales
double orientation(const Point& a, const Point& b, const Point& c) {
    return (b - a).cross(c - a);
}

//valida si el punto C esta entre la linea AB
bool onLine(Point &a, Point &b, Point &c){
    return sgn(orientation(a, b, c)) == 0;
}

//distance from point p to line ab
double distancePointLine(const Point& a, const Point& b, const Point& p) {
    return fabs((b - a).cross(p - a)) / dist(a, b);
}
//distance from point p to segment ab
double distancePointSegment(const Point& a, const Point& b, const Point& p) {
    Point ap = p - a, ab = b - a;
    double t = ap.dot(ab) / ab.norm2();
    if (t < 0.0) return dist(p, a);
    if (t > 1.0) return dist(p, b);
    Point proj = a + ab * t;
    return dist(p, proj);
}

// Check if segments ab and cd intersect
bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    double o1 = orientation(a, b, c);
    double o2 = orientation(a, b, d);
    double o3 = orientation(c, d, a);
    double o4 = orientation(c, d, b);

    if (sgn(o1) * sgn(o2) < 0 && sgn(o3) * sgn(o4) < 0)
        return true; 
    auto onSegment = [&](const Point& p, const Point& q, const Point& r) {
        return min(p.x, r.x) - EPS <= q.x && q.x <= max(p.x, r.x) + EPS &&
               min(p.y, r.y) - EPS <= q.y && q.y <= max(p.y, r.y) + EPS;
    };

    if (sgn(o1) == 0 && onSegment(a, c, b)) return true;
    if (sgn(o2) == 0 && onSegment(a, d, b)) return true;
    if (sgn(o3) == 0 && onSegment(c, a, d)) return true;
    if (sgn(o4) == 0 && onSegment(c, b, d)) return true;

    return false;
}

/*
    /| b
   / |
  /  |
a/---|-c
*/
//angulo interno formado por las lineas ab, ac
//retorna el angulo en radianes
double anguloLineas(Point &a, Point &b, Point &c){
    double ac = dist(a, c);
    double ab = dist(a, b);
    double bc = dist(b, c);

    double a_radianes = ((ac * ac) + (ab * ab) - (bc * bc)) / (2 * ac * ab);
    return acos(a_radianes);
}


//LINEA 
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

Point perp(const Point& a) {
    return Point(-a.y, a.x);
}


//Circuncentro de un triángulo (pasa por A, B, C)
Point circumCenter(Point a, Point b, Point c) {
    b = b - a, c = c - a; // coordenadas relativas a A
    //double d = cross(b, c);
    double d = b.cross(c);
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

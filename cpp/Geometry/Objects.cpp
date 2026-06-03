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
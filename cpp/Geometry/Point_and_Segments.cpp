#include <bits/stdc++.h>
using namespace std;

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

int main() {
    Point A(0, 0), B(4, 4), C(1, 2), D(3, 0);
    Point p1(0,0),p2(1,1),p3(-1,-5);

    cout << "Orientación A,B,C: " << orientation(A, B, C) << "\n";
    cout << "Distancia de C a línea AB: " << distancePointLine(A, B, C) << "\n";
    cout << "Segmentos AB y CD se cruzan: " << (segmentsIntersect(A, B, C, D) ? "Sí" : "No") << "\n";
    cout<<"Orientación p1,p2,p3: "<<orientation(p1,p2,p3)<<"\n";
    return 0;
}

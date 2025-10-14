#include <bits/stdc++.h>
using namespace std;

// ===== CONFIGURACIÓN BASE =====
#define endl '\n'
typedef long double ld;
const ld EPS = 1e-9;
#define eq(a,b) (fabsl((a)-(b)) < EPS)

struct pt {
    ld x, y;
    pt(ld _x=0, ld _y=0): x(_x), y(_y) {}
    pt operator+(pt p) const { return {x+p.x, y+p.y}; }
    pt operator-(pt p) const { return {x-p.x, y-p.y}; }
    pt operator*(ld d) const { return {x*d, y*d}; }
    bool operator==(pt p) const { return eq(x,p.x) && eq(y,p.y); }
    void read() { cin >> x >> y; }
};

ld dot(pt a, pt b) { return a.x*b.x + a.y*b.y; }
ld cross(pt a, pt b) { return a.x*b.y - a.y*b.x; }
ld norm2(pt a) { return a.x*a.x + a.y*a.y; }
ld dist2(pt a, pt b) { return norm2(a - b); }
bool parallel(pt a, pt b) { return eq(cross(a,b), 0); }

// ===== CLASIFICADORES =====

// cuadrado: lados iguales + ángulos rectos
bool isSquare(pt a, pt b, pt c, pt d) {
    ld ab = dist2(a,b), bc = dist2(b,c), cd = dist2(c,d), da = dist2(d,a);
    return eq(ab,bc) && eq(bc,cd) && eq(cd,da)
        && eq(dot(b-a, d-a), 0);
}

// rectángulo: ángulos rectos, lados opuestos iguales
bool isRectangle(pt a, pt b, pt c, pt d) {
    return parallel(a-b, c-d) && parallel(b-c, d-a)
        && eq(dot(b-a, b-c), 0);
}

// rombo: lados iguales
bool isRhombus(pt a, pt b, pt c, pt d) {
    ld ab = dist2(a,b), bc = dist2(b,c), cd = dist2(c,d), da = dist2(d,a);
    return eq(ab,bc) && eq(bc,cd) && eq(cd,da);
}

// paralelogramo: lados opuestos paralelos
bool isParallelogram(pt a, pt b, pt c, pt d) {
    return parallel(a-b, c-d) && parallel(b-c, d-a);
}

// trapecio: un par de lados paralelos
bool isTrapezium(pt a, pt b, pt c, pt d) {
    return parallel(a-b, c-d) ^ parallel(b-c, d-a);
}

// cometa (kite): dos pares de lados adyacentes iguales
bool isKite(pt a, pt b, pt c, pt d) {
    ld ab = dist2(a,b), bc = dist2(b,c), cd = dist2(c,d), da = dist2(d,a);
    return (eq(ab,bc) && eq(cd,da)) || (eq(ab,da) && eq(bc,cd));
}

// ===== PROGRAMA PRINCIPAL =====
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pt a,b,c,d;
    a.read(); b.read(); c.read(); d.read();

    if (isSquare(a,b,c,d)) cout << "square" << endl;
    else if (isRectangle(a,b,c,d)) cout << "rectangle" << endl;
    else if (isRhombus(a,b,c,d)) cout << "rhombus" << endl;
    else if (isParallelogram(a,b,c,d)) cout << "parallelogram" << endl;
    else if (isTrapezium(a,b,c,d)) cout << "trapezium" << endl;
    else if (isKite(a,b,c,d)) cout << "kite" << endl;
    else cout << "none" << endl;

    return 0;
}

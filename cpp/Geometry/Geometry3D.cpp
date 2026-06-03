// geometry3d.hpp
#pragma once
#include <bits/stdc++.h>
using namespace std;

typedef double ld;
const ld DINF = 1e18;
const ld EPS = 1e-9;
inline ld sq(ld x) { return x*x; }
inline bool eq(ld a, ld b) { return fabs(a - b) <= EPS; }

struct pt {
    ld x, y, z;
    pt(ld x_ = 0, ld y_ = 0, ld z_ = 0) : x(x_), y(y_), z(z_) {}
    bool operator < (const pt& p) const {
        if (!eq(x, p.x)) return x < p.x;
        if (!eq(y, p.y)) return y < p.y;
        if (!eq(z, p.z)) return z < p.z;
        return false;
    }
    bool operator == (const pt& p) const {
        return eq(x, p.x) && eq(y, p.y) && eq(z, p.z);
    }
    pt operator + (const pt& p) const { return pt(x + p.x, y + p.y, z + p.z); }
    pt operator - (const pt& p) const { return pt(x - p.x, y - p.y, z - p.z); }
    pt operator * (const ld c) const { return pt(x * c, y * c, z * c); }
    pt operator / (const ld c) const { return pt(x / c, y / c, z / c); }
    // producto escalar
    ld operator * (const pt& p) const { return x * p.x + y * p.y + z * p.z; }
    // producto cruz
    pt operator ^ (const pt& p) const { 
        return pt(y * p.z - z * p.y,
                  z * p.x - x * p.z,
                  x * p.y - y * p.x);
    }
    ld norm2() const { return x*x + y*y + z*z; }
    ld norm() const { return sqrt(norm2()); }
    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y >> p.z;
    }
    friend ostream& operator << (ostream& out, const pt& p) {
        out << "(" << p.x << "," << p.y << "," << p.z << ")";
        return out;
    }
};

inline ld DEG_TO_RAD(ld n) { return n * acos(-1.0) / 180.0; }
inline ld RAD_TO_DEG(ld n) { return n * 180.0 / acos(-1.0); }

struct line {
    pt p, q; // segment from p to q, or line through p in direction (q-p)
    line() {}
    line(pt p_, pt q_) : p(p_), q(q_) {}
    friend istream& operator >> (istream& in, line& r) { return in >> r.p >> r.q; }
};

struct plane {
    array<pt,3> p;    // tres puntos que definen el plano
    array<ld,4> eq;   // ax + by + cz + d = 0
    plane() {}
    plane(pt a, pt b, pt c) : p({a,b,c}) { build(); }
    void build() {
        pt v1 = p[1] - p[0], v2 = p[2] - p[0];
        pt n = v1 ^ v2;
        // eq = {a, b, c, d} con d tal que a*x + b*y + c*z + d = 0
        eq[0] = n.x; eq[1] = n.y; eq[2] = n.z;
        eq[3] = -(n * p[0]);
    }
    friend istream& operator >> (istream& in, plane& P) {
        in >> P.p[0] >> P.p[1] >> P.p[2];
        P.build();
        return in;
    }
};

// convierte de coordenadas esféricas (rho, theta, phi) a cartesianas
// theta = rotación en xy, phi = ángulo desde z (radianes)
inline pt convert(ld rho, ld theta, ld phi) {
    return pt(sin(phi) * cos(theta) * rho,
              sin(phi) * sin(theta) * rho,
              cos(phi) * rho);
}

// proyección de punto p en la recta r
inline pt proj(const pt& p, line r) {
    if (r.p == r.q) return r.p;
    pt dir = r.q - r.p;
    pt v = p - r.p;
    ld t = (v * dir) / dir.norm2();
    return r.p + dir * t;
}

// proyección de punto p en el plano P
inline pt proj(const pt& p, const plane& P) {
    pt v1 = P.p[1] - P.p[0], v2 = P.p[2] - P.p[0];
    pt n = v1 ^ v2;
    if (n.norm2() < EPS) return P.p[0]; // plano degenerado
    // proyectar: p' = p - n * ((n·(p - p0)) / |n|^2)
    ld t = (n * (p - P.p[0])) / n.norm2();
    return p - n * t;
}

// distancia euclidiana
inline ld dist(const pt& a, const pt& b) {
    return (a - b).norm();
}

// distancia de un punto a una recta
inline ld distline(const pt& p, const line& r) {
    return dist(p, proj(p, r));
}

// distancia de punto a segmento
inline ld distseg(const pt& p, const line& r) {
    pt a = r.p, b = r.q;
    pt ab = b - a;
    pt ap = p - a;
    ld d1 = ap * ab;
    if (d1 <= 0) return dist(p, a);
    ld d2 = (p - b) * (a - b); // (p-b)·(a-b)
    if (d2 <= 0) return dist(p, b);
    return distline(p, r);
}

// distancia con signo punto-plano: ax + by + cz + d
inline ld sdist(const pt& p, const plane& P) {
    return P.eq[0]*p.x + P.eq[1]*p.y + P.eq[2]*p.z + P.eq[3];
}
inline ld distplane(const pt& p, const plane& P) { return fabs(sdist(p,P)) / sqrt(sq(P.eq[0]) + sq(P.eq[1]) + sq(P.eq[2])); }

// si punto pertenece al segmento (tolerancia EPS)
inline bool isinseg(const pt& p, const line& r) {
    return eq(distseg(p, r), 0.0);
}

// --- PUNTO EN POLÍGONO 3D ---
// Proyecta polígono y punto al plano principal del polígono y aplica ray-casting 2D.
// Devuelve true si p está dentro o en el borde del polígono (polígono simple, no necesariamente convexo).
inline bool pointInPolygon3D(const pt& p, const vector<pt>& poly) {
    int n = poly.size();
    assert(n >= 3);
    // construir plano del polígono
    plane P(poly[0], poly[1], poly[2]);
    // proyectar punto y polígono al sistema de coordenadas 2D local
    // Elegimos dos ejes ortonormales u,v en el plano
    pt u = (poly[1] - poly[0]);
    if (u.norm() < EPS) return false;
    u = u / u.norm();
    pt nrm = (poly[1] - poly[0]) ^ (poly[2] - poly[0]);
    if (nrm.norm() < EPS) return false;
    nrm = nrm / nrm.norm();
    pt v = nrm ^ u; // v es ortogonal a u en el plano

    auto to2d = [&](const pt& q)->pair<ld,ld> {
        pt rel = q - poly[0];
        return { rel * u, rel * v }; // coordenadas (x,y)
    };

    pair<ld,ld> pp = to2d(proj(p, P)); // proyectamos p al plano del polígono
    vector<pair<ld,ld>> poly2(n);
    for (int i = 0; i < n; ++i) poly2[i] = to2d(poly[i]);

    // Punto en segmento (2D)
    auto onSeg2D = [&](pair<ld,ld> a, pair<ld,ld> b, pair<ld,ld> q)->bool {
        ld minx = min(a.first, b.first)-EPS, maxx = max(a.first, b.first)+EPS;
        ld miny = min(a.second, b.second)-EPS, maxy = max(a.second, b.second)+EPS;
        // area (a,b,q)
        ld cross = (b.first - a.first) * (q.second - a.second) - (b.second - a.second) * (q.first - a.first);
        return fabs(cross) <= EPS && q.first >= minx && q.first <= maxx && q.second >= miny && q.second <= maxy;
    };

    // Ray casting 2D
    bool inside = false;
    for (int i = 0, j = n-1; i < n; j = i++) {
        auto a = poly2[i], b = poly2[j];
        if (onSeg2D(a,b,pp)) return true;
        bool intersect = ((a.second > pp.second) != (b.second > pp.second))
                       && (pp.first < (b.first - a.first) * (pp.second - a.second) / (b.second - a.second) + a.first);
        if (intersect) inside = !inside;
    }
    return inside;
}

// distancia de punto a polígono (polígono simple en 3D)
// si la proyección del punto cae dentro del polígono, la distancia es la distancia perpendicular al plano,
// si no, la mínima distancia a aristas
inline ld distpol(const pt& p, const vector<pt>& poly) {
    int n = poly.size();
    assert(n >= 3);
    plane P(poly[0], poly[1], poly[2]);

    pt pproj = proj(p, P);
    if (pointInPolygon3D(p, poly)) return dist(p, pproj);

    ld best = DINF;
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n;
        best = min(best, distseg(p, line(poly[i], poly[j])));
    }
    return best;
}

// Intersección segmento-plano
enum RETCODE { BOTH, ONE, PARAL, CONCOR };
inline pair<RETCODE, pt> intersect(const plane& P, const line& r) {
    ld d1 = sdist(r.p, P);
    ld d2 = sdist(r.q, P);
    if (eq(d1, 0) && eq(d2, 0)) return {BOTH, r.p};
    if (eq(d1, 0)) return {ONE, r.p};
    if (eq(d2, 0)) return {ONE, r.q};
    if ((d1 > 0 && d2 > 0) || (d1 < 0 && d2 < 0)) {
        if (eq(d1 - d2, 0)) return {PARAL, pt()};
        return {CONCOR, pt()};
    }
    ld frac = d1 / (d1 - d2);
    pt res = r.p + (r.q - r.p) * frac;
    return {ONE, res};
}

// Rotación de p alrededor del eje definido por u (vector que pasa por origen) por ángulo a (radianes).
// Usamos fórmula de Rodrigues:
// p_rot = p*cos(a) + (u x p)*sin(a) + u*(u·p)*(1 - cos(a)), con u normalizado.
inline pt rotate(const pt& p, pt u, ld a) {
    ld un = u.norm();
    if (un < EPS) return p; // eje inválido
    u = u / un;
    ld cosa = cos(a), sina = sin(a);
    pt term1 = p * cosa;
    pt term2 = (u ^ p) * sina;
    pt term3 = u * ((u * p) * (1 - cosa));
    return term1 + term2 + term3;
}

// ------------------- Ejemplo de uso rápido -------------------
#ifdef GEOMETRY3D_TEST_MAIN
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // test básicos
    pt A(0,0,0), B(1,0,0), C(0,1,0), P(0.2,0.2,1);
    plane pl(A,B,C);
    cout << "Distancia punto-plano (P): " << distplane(P, pl) << "\n";
    cout << "Proyección de P en plano: " << proj(P, pl) << "\n";

    vector<pt> poly = {A, B, pt(1,1,0), C}; // cuadrado en z=0
    cout << "P en polígono? " << (pointInPolygon3D(P, poly) ? "si" : "no") << "\n";
    pt P2(0.5,0.5,0.5);
    cout << "distpol(P2) = " << distpol(P2, poly) << "\n";

    // rotar punto (1,0,0) 90 grados alrededor del eje z
    pt p(1,0,0), axis(0,0,1);
    pt r = rotate(p, axis, DEG_TO_RAD(90.0));
    cout << "Rotado 90 deg alrededor de z: " << r << "\n";

    return 0;
}
#endif

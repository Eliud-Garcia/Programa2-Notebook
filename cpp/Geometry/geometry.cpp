

/*
razones trigonometricas

CO = cateto opuesto
CA = cateto adyacente
H = hipotenusa

sin(angulo) = CO / H
cos(angulo) = CA / H
tan(angulo) = CO / CA

sosecante(angulo) = H / CO
secante(angulo) = H / CA
cotangente(angulo) = CA / CO 
*/

using ld = long double;

struct point {
    ll x, y, id;
    point(ll a = 0, ll b = 0, int i = -1) {
        x = a;
        y = b;
        id = i;
    }

    point operator -(const point b) {
        return point(x - b.x, y - b.y, -1);
    }

    //cross(a, b) producto escalar
    ll operator ^(const point b) {
        return x * b.y - y * b.x;
    }

    ll operator *(const point b) {
        return x * b.x + y * b.y;
    }
};

ld norm(point a) { // Modulo
    return sqrt(a * a);
}

// ======= POLAR SORT =======
int ret[2][2] = {{3, 2}, {4, 1}};
inline int quad(point p) {
    return ret[p.x >= 0][p.y >= 0];
}

//points sorted in counterclockwise order
bool comp(point a, point b) { // ccw
    int qa = quad(a), qb = quad(b);
    return (qa == qb ? (a ^ b) > 0 : qa < qb);
}

// ======= POLAR SORT =======

// ang(a1,b1) <= ang(a2,b2)
bool angle_less(point a1, point b1, point a2, point b2) {
    point p1((a1 * b1), abs((a1 ^ b1)));
    point p2((a2 * b2), abs((a2 ^ b2)));
    return (p1 ^ p2) <= 0;
}

int main() {
    //dados n vectores
    //todos con origen en (0, 0)
    //hallar dos vectores  diferentes
    //que forman el angulo minimo
    int n;
    cin >> n;
    vector<point> pts(n);

    forn(i, n) {
        ll x, y;
        cin >> x >> y;
        pts[i] = point(x, y, i + 1);
    }

    sort(all(pts), comp);
    array<point, 2> ans = {pts[0], pts[n - 1]};
    forab(i, 1, n) {
        if(angle_less(ans[0], ans[1], pts[i], pts[i - 1])) {
            ans = {pts[i], pts[i - 1]};
        }
    }
    cout << ans[0].id << " " << ans[1].id << ln;
    return 0;
}

#define sq(x) ((x)*(ll)(x))

struct pt { // punto
    ll x, y;
    pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
    bool operator < (const pt p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator == (const pt p) const {
        return x == p.x and y == p.y;
    }
    pt operator + (const pt p) const {
        return pt(x+p.x, y+p.y);
    }
    pt operator - (const pt p) const {
        return pt(x-p.x, y-p.y);
    }
    pt operator * (const ll c) const {
        return pt(x*c, y*c);
    }
    ll operator * (const pt p) const {
        return x*(ll)p.x + y*(ll)p.y;
    }
    ll operator ^ (const pt p) const {
        return x*(ll)p.y - y*(ll)p.x;
    }
    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y;
    }
};


class ConvexHull {
public:
    int n;
    vector<pt> compute(vector<pt> &pts) {
        n = sz(pts);
        // sort points by x-axis, and by the y-axis when there's a tie.
        sort(pts.begin(), pts.end(), [](pt &a, pt &b) {
            if (b.x < a.x) return false;
            if (b.x == a.x) return a.y > b.y;
            return true;
        });
        auto low_p = lower_hull(pts);
        auto upp_p = upper_hull(pts);

        vector<pt> hull;
        for(auto i: low_p) hull.pb(i);
        for(auto i: upp_p) hull.pb(i);

        sort(all(hull));
        hull.erase(unique(all(hull)), hull.end());
        return hull;
    }

    vector<pt> lower_hull(vector<pt> &pts) {
        vector<pt> stk;
        for (int i = 0; i < n; i++) {
            while (sz(stk) > 1 && is_cwm(stk[sz(stk) - 2], stk.back(), pts[i]))
                stk.pop_back();
            stk.pb(pts[i]);
        }
        return stk;
    }
    vector<pt> upper_hull(vector<pt> &pts) {
        vector<pt> stk;
        for (int i = n - 1; i >= 0; i--) {
            while (sz(stk) > 1 && is_cwm(stk[sz(stk) - 2], stk.back(), pts[i]))
                stk.pop_back();
            stk.pb(pts[i]);
        }
        return stk;
    }
    //isClockWiseMovement
    bool is_cwm(pt &a, pt &b, pt &c) {
        return cross_p(a, b, c) > 0;
    }
    //cross product
    ll cross_p(pt &a, pt &b, pt &c) {
        return ((a.x - b.x) * (c.y - b.y)) - ((a.y - b.y) * (c.x - b.x));
    }
};

int main() {
    int n;
    cin >> n;
    vector<pt> pts(n);
    forn(i, n) {
        cin >> pts[i];
    }

    ConvexHull convexHull;
    vector<pt > ans = convexHull.compute(pts);

    cout << sz(ans) << ln;
    for (auto &p: ans)
        cout << p.x << " " << p.y << ln;

    return 0;
}

//https://cses.fi/problemset/task/2195/

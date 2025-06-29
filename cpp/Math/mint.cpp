
const ll MOD = 1e9 + 7;

struct mint {
    ll v;

    mint() : v(0) {}
    mint(ll x) : v(x % MOD) {
        if (v < 0) v += MOD;
    }

    mint &operator++() { //a++
        v++;
        if (v == MOD) v = 0;
        return *this;
    }

    mint &operator--() { //a--
        if (v == 0) v = MOD;
        v--;
        return *this;
    }
    mint &operator+=(const mint &other) { //a += b
        v += other.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mint &operator-=(const mint &other) { //a -= b
        v -= other.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mint &operator*=(const mint &other) { //a *= b
        v = ll(ll(v) * ll(other.v) % MOD);
        return *this;
    }
    mint &operator/=(const mint &other) { // a /= b
        return *this *= other.inv();
    }

    friend mint operator+(const mint &a, const mint &b) {
        return mint(a) += b;
    }
    friend mint operator-(const mint &a, const mint &b) {
        return mint(a) -= b;
    }
    friend mint operator*(const mint &a, const mint &b) {
        return mint(a) *= b;
    }
    friend mint operator/(const mint &a, const mint &b) {
        return mint(a) /= b;
    }

    friend mint power(mint a, ll p) { // pow(a, p)
        mint res = 1;
        while (p > 0) {
            if (p % 2 == 1)
                res *= a;
            p >>= 1;
            a *= a;
        }
        return res;
    }

    static ll minv(ll a, ll m) {
        a %= m;
        assert(a);
        return a == 1 ? 1 : ll(m - ll(minv(m, a)) * ll(m) / a);
    }

    friend bool operator==(const mint &a, const mint &b) {
        return a.v == b.v;
    }
    friend bool operator!=(const mint &a, const mint &b) {
        return a.v != b.v;
    }
    friend bool operator>(const mint &a, const mint &b) {
        return a.v > b.v;
    }
    friend bool operator<(const mint &a, const mint &b) {
        return a.v < b.v;
    }

    mint neg() const {
        mint res;
        res.v = v ? MOD - v : 0;
        return res;
    }

    friend mint neg(const mint &m) {
        return m.neg();
    }

    mint inv() const {
        mint res;
        res.v = minv(v, MOD);
        return res;
    }

    friend mint inv(const mint &m) {
        return m.inv();
    }

    mint operator-() const {
        return neg();
    }
    mint operator+() const {
        return mint(*this);
    }
};

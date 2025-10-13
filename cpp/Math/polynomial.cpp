#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const double EPS = 1e-9;
const ll mod = 1000000007;

typedef int tp;

template <class T = tp>
struct poly
{
    vector<T> c;
    poly() {}
    poly(initializer_list<T> v) : c(v) {}
    poly(const vector<T> &v) : c(v) {}
    poly(int n) : c(n) {}

    T &operator[](int i) { return c[i]; }
    const T &operator[](int i) const { return c[i]; }

    poly operator+(const poly &o) const
    {
        int m = c.size(), n = o.c.size();
        poly res(max(m, n));
        for (int i = 0; i < m; i++)
            res[i] += c[i];
        for (int i = 0; i < n; i++)
            res[i] += o.c[i];
        return res;
    }

    poly operator*(tp k) const
    {
        poly res(c.size());
        for (int i = 0; i < (int)c.size(); i++)
            res[i] = c[i] * k;
        return res;
    }

    poly operator*(const poly &o) const
    {
        int m = c.size(), n = o.c.size();
        poly res(m + n - 1);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res[i + j] += c[i] * o.c[j];
        return res;
    }

    poly operator-(const poly &o) const { return *this + (o * -1); }

    T operator()(tp v) const
    {
        T sum = 0;
        for (int i = (int)c.size() - 1; i >= 0; --i)
            sum = sum * v + c[i];
        return sum;
    }
};

// -------- Métodos adicionales --------

// raíces enteras posibles
set<tp> roots(poly<> p)
{
    set<tp> r;
    while (!p.c.empty() && !p.c.back())
        p.c.pop_back();
    if (p.c.empty())
        return r;
    if (p(0) == 0)
        r.insert(0);

    tp a0 = 0, an = abs(p[p.c.size() - 1]);
    for (int k = 0; !a0;)
        a0 = abs(p[k++]);

    vector<tp> ps, qs;
    for (int i = 1; i * i <= a0; i++)
        if (a0 % i == 0)
        {
            ps.push_back(i);
            ps.push_back(a0 / i);
        }
    for (int i = 1; i * i <= an; i++)
        if (an % i == 0)
        {
            qs.push_back(i);
            qs.push_back(an / i);
        }

    for (auto pt : ps)
        for (auto qt : qs)
            if (pt % qt == 0)
            {
                tp x = pt / qt;
                if (p(x) == 0)
                    r.insert(x);
                if (p(-x) == 0)
                    r.insert(-x);
            }
    return r;
}

// División sintética (Ruffini)
pair<poly<>, tp> ruffini(poly<> p, tp r)
{
    int n = p.c.size() - 1;
    vector<tp> b(n);
    b[n - 1] = p[n];
    for (int k = n - 2; k >= 0; --k)
        b[k] = p[k + 1] + r * b[k + 1];
    return {poly<>(b), p[0] + r * b[0]};
}

// División polinómica (double)
pair<poly<>, poly<>> polydiv(poly<> p, poly<> q)
{
    int n = p.c.size() - q.c.size() + 1;
    vector<tp> b(n);
    for (int k = n - 1; k >= 0; --k)
    {
        b[k] = p.c.back() / q.c.back();
        for (int i = 0; i < (int)q.c.size(); i++)
            p[i + k] -= b[k] * q[i];
        p.c.pop_back();
    }
    while (!p.c.empty() && fabs(p.c.back()) < EPS)
        p.c.pop_back();
    return {poly<>(b), p};
}

// Interpolación de Lagrange
poly<> interpolate(vector<tp> x, vector<tp> y)
{
    poly<> q = {1}, S = {0};
    for (tp a : x)
        q = poly<>({-a, 1}) * q;
    for (int i = 0; i < (int)x.size(); i++)
    {
        auto Li = ruffini(q, x[i]).first;
        Li = Li * (1.0 / Li(x[i])); // para int habría que usar fracciones
        S = S + Li * y[i];
    }
    return S;
}

// Construcción a partir de raíces
vector<ll> coef(vector<ll> roots, bool first = true)
{
    int l = roots.size() + 1;
    vector<ll> c(10002, 0), m(10002, 0);
    c[0] = 1;
    for (int k = 0; k < (int)roots.size(); k++)
    {
        for (int i = 1; i < l; i++)
            m[i] = c[i] + c[i - 1] * roots[k];
        for (int i = 1; i < l; i++)
            c[i] = m[i];
    }
    ll sign = first ? 1 : -1;
    for (int i = 0; i < (int)roots.size(); i++)
    {
        sign *= -1LL;
        m[i + 1] *= sign;
    }
    return m;
}

// módulo seguro
inline ll modn(ll x)
{
    x %= mod;
    if (x < 0)
        x += mod;
    return x;
}

// Interpolación rápida modular
ll interpolateAndEvaluate(ll k, int inix, vector<ll> &y)
{
    ll den = 1, num = 1;
    int len = inix + y.size() - 1;
    for (int i = inix; i < len; i++)
    {
        num = (num * (k - (i + 1))) % mod;
        den = (den * modn(-1ll * i)) % mod;
    }
    auto divmod = [&](ll a, ll b)
    { return a * 1LL * std::pow(b, mod - 2) % mod; }; // suponiendo mod primo

    ll res = (y[0] * divmod(num, den)) % mod;
    return res;
}

// -------- Ejemplo --------
int main()
{
    poly<> p = {-6, 11, -6, 1}; //-6 + 11x - 6x^2 + x^3
    cout << "p(1) = " << p(1) << "\n";

    auto r = roots(p);
    cout << "Raices enteras: ";
    for (auto x : r)
        cout << x << " ";
    cout << "\n";

    auto d = ruffini(p, 1);
    cout << "Division por (x-1): resto=" << d.second << "\n";

    return 0;
}

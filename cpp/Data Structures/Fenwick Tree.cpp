
//[1, n]
//rangos [l, r]

template <typename T>
struct BIT {
    vector<T> ft;
    int N;
    BIT(int n): ft(n + 1), N(n) {}

    BIT(const vector<T>& a): ft(sz(a) + 1), N(sz(a)) {
        forn(i, sz(a)) {
            upd(i + 1, a[i]);
        }
    }

    T qry(int i) {
        T ans = 0;
        for (; i; i -= i & -i) ans += ft[i];
        return ans;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int i, T v) {
        for (; i < sz(ft); i += i & -i) ft[i] += v;
    }
    //This is equivalent to calculating
    //lower_bound on prefix sums array
    int bit_search(int v) { // O(log(N))
        int sum = 0;
        int pos = 0;
        int LOGN = int(log2(N));
        for (int i = LOGN; i >= 0; i--) {
            ll acum = sum + ft[pos + (1 << i)];
            if (pos + (1 << i) < N && acum < v) {
                sum += ft[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
    }
    //sin palabras x
};

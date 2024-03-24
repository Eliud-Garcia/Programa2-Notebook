
template <typename T>
struct BIT {
    vector<T> ft;
    int N;
    BIT(int n): ft(n + 1), N(n){}

    BIT(const vector<T>& a): ft(sz(a) + 1), N(sz(a)){
        forn(i, sz(a)) { upd(i + 1, a[i]); }
    }

    T qry(int i){
        T ans = 0;
        for (; i; i -= i & -i) ans += ft[i];
        return ans;
    }

    T qry(int l, int r){
        return qry(r) - qry(l - 1);
    }

    void upd(int i, T v){
        for (; i < sz(ft); i += i & -i) ft[i] += v;
    }
    //This is equivalent to calculating 
    //lower_bound on prefix sums array
    int bit_search(int v){ // O(log(N))
        int sum = 0;
        int pos = 0;
        int LOGN = (int)(log(N) / log(2));
        for (int i = LOGN; i >= 0; i--) {
            if (pos + (1 << i) < N && sum + ft[pos + (1 << i)] < v) {
                sum += ft[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1; 
        // +1 because 'pos' will have position of largest value less than 'v'
    }
};

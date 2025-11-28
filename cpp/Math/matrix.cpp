
const int MOD = 1e9 + 7;

struct matrix {
    int n, m;
    vector<vector<int>> v;

    matrix(int n, int m, bool ones = false) : n(n), m(m), v(n, vector<int>(m)) {
        if (ones)
            forn(i, n) v[i][i] = 1;
    }

    void reset(){
        forn(i, m) v[0][i] = 0;
        v[0][m - 1] = 1;
    }

    matrix operator*(const matrix &o) {
        matrix ans(n, o.m);
        forn(i, n) 
            forn(k, m) if (v[i][k]) 
                forn(j, o.m) ans[i][j] =
                    (1ll * v[i][k] * o.v[k][j] + ans[i][j]) % MOD;
        return ans;
    }

    vector<int> &operator[](int i) { return v[i]; }
};


matrix binpow(matrix b, ll e) {
    matrix ans(1, 4);
    ans.reset(); //define la base
    while (e) {
        if (e & 1)
            ans = ans * b;
        b = b * b;
        e >>= 1;
    }
    return ans;
}

int main() {
    int n;
    while((cin >> n)){
        matrix m(4, 4);
        
        forn(i, 4){
            forn(j, 4){
                if(i == j) m[i][j] = 0;
                else m[i][j] = 1;
            }
        }
        
        matrix ans = binpow(m, n);
        cout << ans[0][3] << ln;

    }
    return 0;
}


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll MOD = 991831889LL;

//9982443539LL
//1000000007LL
//1000000009LL

const ll C = uniform_int_distribution<ll>(0.1 * MOD, 0.9 * MOD)(rng);

struct hash_str {
    vll h, p;
    hash_str(const string &s) : h(sz(s) + 1), p(sz(s) + 1) {
        p[0] = 1;
        h[0] = 0;
        forn (i, sz(s)) {
            h[i + 1] = (C * h[i] + s[i]) % MOD;
            p[i + 1] = (C * p[i]) % MOD;
        }
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    ll get(int a, int b) {
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % MOD) + MOD) % MOD;
    }
};


bool is_pal(int l, int r,  hash_str &h1,  hash_str &h2) {
    int l2 = sz(h1.h) - 2 - r;
    int r2 = sz(h1.h) - 2 - l;
    return (h1.get(l, r) == h2.get(l2, r2));
}

//how many substrings of a given string are palindromes.
ll count_palindromes(string &s, hash_str &h1, hash_str &h2) {
    ll ans = 0;

    forn(i, sz(s)) {
        // Palindromes odd length
        int l = 0, r = min(i + 1, sz(s) - i);
        while (l < r) {
            ll mid = (l + r + 1) / 2;
            if (is_pal(i - mid + 1, i + mid - 1, h1, h2)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        ans += l;

        //Palindromes even length
        l = 0, r = min(i + 1, sz(s) - i - 1);
        while (l < r) {
            ll mid = (l + r + 1) / 2;
            if (is_pal(i - mid + 1, i + mid, h1, h2)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        ans += l;
    }

    return ans;
}

int main() {
    string s;
    cin >> s;

    //normal hash
    hash_str h1(s);

    //reverse hash
    string rev_s = s;
    reverse(all(rev_s));
    hash_str h2(rev_s);

    ll ans = count_palindromes(s, h1, h2);
    cout << ans << ln;
    return 0;
}

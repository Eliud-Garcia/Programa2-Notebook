
struct hash_str {
    ll c, mod;
    vll h, p;
    hash_str(const string &s, ll c, ll mod) : c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1) {
        p[0] = 1;
        h[0] = 0;
        forn (i, sz(s)) {
            h[i + 1] = (c * h[i] + s[i]) % mod;
            p[i + 1] = (c * p[i]) % mod;
        }
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    ll get(int a, int b) {
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
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
    ll mod = 1e9 + 7;
    string s;
    cin >> s;

    //normal hash
    hash_str h1(s, 131, mod);

    //reverse hash
    string rev_s = s;
    reverse(all(rev_s));
    hash_str h2(rev_s, 131, mod);

    ll ans = count_palindromes(s, h1, h2);
    cout << ans << ln;
    return 0;
}

//Tener ciudado con el signo $ concatenar puede dar TLE
//solo en unique_substrings no se necesita pasar la cadena con "$"

const int ALP = 256; //alfabeto

vi suffix_array(const string &s) { //s con $
    int n = sz(s), cl = 1;
    vi c(n), p(n), cn(n), pn(n), cnt(max(n, ALP), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < ALP; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if(s[p[i]] != s[p[i - 1]]) cl++;
        c[p[i]] = cl - 1;
    }
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < cl; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cl = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prv = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if(cur != prv) cl++;
            cn[p[i]] = cl - 1;
        }
        cn.swap(c);
    }
    return p;
}

int bin_search(const string &s, const string &t, bool lower, vi &sa){ //s con %
int l = 0, r = sz(s) - 1, ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        bool ls = false, ok = true;
        for (int k = 0; k < sz(t); k++) {
            if (t[k] < s[sa[mid] + k]) {
                ls = true, ok = false;
                break;
            }
            if (t[k] > s[sa[mid] + k]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = mid;
            if (lower) r = mid - 1;
            else l = mid + 1;
        } else {
            if (ls) r = mid - 1;
            else l = mid + 1;
        }
    }
    return ans;
}

//cuantas veces aparece w en s
int count_occ(const string &s, const string &w, vi &sa){ //s con $
    int low = bin_search(s, w, true, sa);
    if(low == -1){
        return 0;
    }
    int up = bin_search(s, w, false, sa);
    return up - low + 1;
}

vi kasai(const string& s, vi &sa) { //s con $
    int n = sz(s);
    vi lcp(n), inv(n);
    forab (i, 0, n){ inv[sa[i]] = i;}
    for (int i = 0, k = 0; i < n; i++) {
        if (inv[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[inv[i] + 1];
        while ((i + k < n) && (j + k < n) && s[i + k] == s[j + k])
            k++;
        lcp[inv[i]] = k;
        if (k > 0)
            k--;
    }
    return lcp;
}

ll unique_substrings(const string &s, vi &sa, vi &lcp) { //s sin $
    int n = sz(s);
    ll ans = n - sa[0];
    forab (i, 1, sz(lcp)) {
        ans += (n - sa[i]) - lcp[i - 1];
    }
    return ans;
}

int main() {
    string s; cin >> s;
    s += "$";
    vi sa = suffix_array(s);
    vi lcp = kasai(s, sa);
    /*
    s.pop_back();
    cout << unique_substrings(s, sa, lcp) << ln;
    */
    int q; cin >> q;
    while(q--){
        string w;
        cin >> w;
        cout << count_occ(s, w, sa) << ln;
    }

    /** banana
    0 = banana$
    1 = anana$
    2 = nana$
    3 = ana$
    4 = na$
    5 = a$
    6 = $

    sa = 5, 3, 1, 0, 4, 2
    */
    return 0;
}
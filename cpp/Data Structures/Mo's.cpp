
int S, n, q;

struct query {
    int l, r, idx;
    query(int l, int r, int idx): l(l), r(r), idx(idx) {}

    bool operator < (const query &x) const {
        if (l / S != x.l / S) return l / S < x.l / S;
        return (l / S & 1) ?  r < x.r: r > x.r;
    }
};

const int MAXN = 1e6 + 1;
ll sum = 0;
vector<query> qu;
vector<ll> ans;
vi feq(MAXN, 0);
vll a;

void add(int idx) {
    ll val = a[idx];
    sum = sum -  (val * feq[val] * feq[val]);
    feq[val]++;
    sum = sum +  (val * feq[val] * feq[val]);
}

/*
Very common pattern:
Subtract power of element from total
Update count
Add back power of element to total
*/
void del(int idx) {
    ll val = a[idx];
    sum = sum - (val * feq[val] * feq[val]);
    feq[val]--;
    sum = sum + (val * feq[val] * feq[val]);
}

ll get_ans() {
    return sum;
}

void mo_s() {
    S = sqrt(n);
    sort(all(qu));
    ans.resize(q);
    int l = 0, r = -1;
    for (query &it: qu) {
        while (r < it.r) add(++r);
        while (l > it.l) add(--l);
        while (r > it.r) del(r--);
        while (l < it.l) del(l++);
        ans[it.idx] = get_ans();
    }
}

int main() {
    cin >> n >> q;
    a = vll(n);
    forn(i, n) cin >> a[i];

    int l, r;
    forn(i, q) {
        cin >> l >> r;
        l--;
        r--;
        qu.pb({l, r, i});
    }
    mo_s();
    forn(i, q) cout << ans[i] << ln;
    return 0;
}




//usar Hash_str aqui

int n;

//retorna si tiene centro
//si es par el centro es unico
//si es impar el centro es doble EJ: bbaabb

int check(int mid, bool even, hash_str &h1, hash_str &h2) {
    forab(i, 0, n) {
        int left = i - mid + (even ? 1 : 0);
        int right = i + mid;
        if (left >= 0 && right < n) {
            if (is_pal(left, right, h1, h2)) return i;
        }
    }
    return -1;
}

//indicar si se busca una cadena par o impar
string solve(string &s, bool even, hash_str &h1, hash_str &h2) {
    int pos = 0;
    int l = -1, r = n;
    while (l + 1 < r) {
        int m = l + (r - l) / 2;
        int centro = check(m, even, h1, h2);
        if (centro != -1) {
            l = m;
            pos = centro;
        } else {
            r = m;
        }
    }

    int len = even ? 2 * l : 2 * l + 1;
    int start = even ? pos - l + 1 : pos - l;

    start = max(0, start);
    len = max(0, len);
    return s.substr(start, len);
}


int main() {
    string s;
    cin >> s;
    n = sz(s);
    hash_str h1(s);
    reverse(all(s));
    string rev = s;
    hash_str h2(rev);

    reverse(all(s));


    string odd = solve(s, 0, h1, h2);
    string even = solve(s, 1, h1, h2);

    if(sz(odd) < sz(even)) swap(even, odd);
    cout << odd << ln;
    return 0;
}

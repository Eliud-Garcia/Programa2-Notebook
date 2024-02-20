
//todos los divisores n en O(sqrt(n))
vi divisors(ll n){
    vi div;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i == n) {
                div.pb(i);
            } else {
                div.pb(i);
                if (i != 1) {
                    div.pb(n / i);
                }
            }
        }
    }
    return div;
}
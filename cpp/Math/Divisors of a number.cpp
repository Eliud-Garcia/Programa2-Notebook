//todos los divisores n en O(sqrt(n))
vll divisors(ll n) {
    vll div;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            div.pb(i);
            if ((n/i) != i)
                div.pb(n / i);
        }
    }
    return div;
}

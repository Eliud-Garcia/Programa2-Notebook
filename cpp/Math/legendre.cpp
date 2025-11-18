
//fórmula de Legendre
//calcula el exponente del mayor primo p que divide a n!
ll legendre(ll n, ll p){
    ll ans = 0;
    for(ll i = p; i <= n; i *= p){
        ans += (n / i);
    }
    return ans;
}

/*
dado m y n
validar si m divide a n!

descomponer m en factores primos
validar para todo p^ex es <= p^legendre(n, p)

UVA 10139
*/
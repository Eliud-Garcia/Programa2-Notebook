Operaciones a nivel de bits.

n & 1		-> Verifica si n es impar o no
n & (1<<k)	-> Verifica si el k-esimo bit esta encendido o no
n | (1<<k)	-> Enciende el k-esimo bit
n & ~(1<<k)	-> Apaga el k-esimo bit
n ^ (1<<k)	-> Invierte el k-esimo bit
~n		    -> Invierte todos los bits
n & -n		-> Devuelve el bit encendido mas a la derecha
~n & (n+1)	-> Devuelve el bit apagado mas a la derecha
n | (n+1)	-> Enciende el bit apagado mas a la derecha
n & (n-1)	-> Apaga el bit encendido mas a la derecha

__builtin_popcountll(x) -> Cuantos bits tiene encendidos


//sumatoria de bits encendidos en el rango [l, r]
//sumatoria de log2 en el rango [l, r]

ll count_bits(ll n){
    ll ans = 0;
    // se trabaja con cada bit independientemente
    forn(i, 61){
        ll total = (1LL << (i + 1));
        ll pattern = (n / total);
        ans += (pattern * total / 2);
        ll remain = n % total;
        if(remain - total / 2 > 0) ans += (remain - total / 2);

    }
    return ans;
}

ll count_logs(ll n){
    if(n == 0) return 0;
    ll cur = 0;
    int i = 0;
    ll ans = 0;
    while(cur < n){
        cur += (1LL << i);
        ans += i * (1LL << i);
        i++;
    }
    i--;
    ll res = abs(cur - n + 1) * i;
    return ans - res;
}

    ll l, r;
    cin >> l >> r;
    ll sum_bits = count_bits(r + 1) - count_bits(l);
    ll sum_logs = count_logs(r + 1) - count_logs(l);
    cout << sum_logs + sum_bits << ln;


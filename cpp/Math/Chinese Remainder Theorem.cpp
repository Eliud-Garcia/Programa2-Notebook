

//tomado de: https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica
using ll = long long;

template<typename T> tuple<T, T, T> ext_gcd(T a, T b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd(b % a, a);
    return {g, y - b / a * x, x};
}

template<typename T = ll> struct crt {
	T a, m;

	crt() : a(0), m(1) {}
	crt(T a_, T m_) : a(a_), m(m_) {}
	crt operator * (crt C) {
		auto [g, x, y] = ext_gcd(m, C.m);
		if ((a - C.a) % g) a = -1;
		if (a == -1 or C.a == -1) return crt(-1, 0);
		T lcm = m / g * C.m;
		T ans = a + (x * (C.a - a)/ g % (C.m / g)) * m;
		return crt((ans % lcm + lcm) % lcm, lcm);
	}
};

/*
    x = a (mod m)

    x = 3 (mod 6)
    x = 4 (mod 5)
    x = 3 (mod 4)
    x = 0 (mod 3)
    x = 1 (mod 2)
    x = 0 (mod 1)

    hallar valor de x
    x = 39 (mod 60)

    retorna (a, m)
    a = 39
    m = 60

    funciona para modulos
    coprimos y no coprimos
    El último m es el mínimo común múltiplo de los m,
    y la solución es única módulo el mínimo común múltiplo.
*/

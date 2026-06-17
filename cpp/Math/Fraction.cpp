
using T = ll; // definir tipo de dato
struct frac {
    T num, den;
    
    frac(T num_ = 0, T den_ = 1) : num(num_), den(den_) {
        assert(den != 0);
        if (den < 0) num *= -1, den *= -1;
        T g = __gcd(abs(num), den);
        num /= g, den /= g;
    }
    
    friend bool operator<(const frac& l, const frac& r) {
        return l.num * r.den < r.num * l.den;
    }
    
    friend frac operator+(const frac& l, const frac& r) {
        T g = __gcd(l.den, r.den);
        T new_den = l.den / g * r.den;
        T new_num = l.num * (r.den / g) + r.num * (l.den / g);
        return {new_num, new_den};
    }
    
    friend frac operator-(const frac& l, const frac& r) {
        T g = __gcd(l.den, r.den);
        T new_den = l.den / g * r.den;
        T new_num = l.num * (r.den / g) - r.num * (l.den / g);
        return {new_num, new_den};
    }
    
    friend frac operator*(const frac& l, const frac& r) {
        // Simplificacion cruzada antes de multiplicar
        T g1 = __gcd(abs(l.num), r.den);
        T g2 = __gcd(abs(r.num), l.den);
        return {(l.num / g1) * (r.num / g2), (l.den / g2) * (r.den / g1)};
    }
    
    friend frac operator/(const frac& l, const frac& r) {
        assert(r.num != 0);
        // Equivale a l * (r invertido)
        T g1 = __gcd(abs(l.num), abs(r.num));
        T g2 = __gcd(l.den, r.den);
        return {(l.num / g1) * (r.den / g2), (l.den / g2) * (r.num / g1)};
    }
    
    friend ostream& operator<<(ostream& out, frac f) {
        out << f.num << '/' << f.den;
        return out;
    }
};
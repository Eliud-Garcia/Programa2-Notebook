
ll euclid(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll xi, yi;
    ll g = euclid(b, a % b, xi, yi);
    x = yi;
    y = xi  - yi * (a / b);
    return g;
}

int main() {
    //hallar Ax + By + C = 0
    ll a, b, c;
    cin >> a >> b >> c;
    ll x, y;
    ll g = euclid(a, b, x, y);
    if(c % g) cout << "-1" << ln;
    else cout << (-(c / g) * x) << " " << (-(c / g) * y) << ln;
    return 0;
}

/*
    g = gcd(a, b)
    a*x + b*y = g

    se quiere que 
    a*x + b*y = c

    usamos el Extended Euclidean Algorithm
    y multiplicamos a ambos lados por (c / gcd(a, b))
    a * (c / g) * x + b * (c / g) * y
    mas simple
    x *= (c / g)
    y *= (c / g)
    
    rango de la respuesta t
    (-x / (b / g)) <= t <= (y / (a / g))

    x0 = -x + (b / g) * t
    y0 = y - (a / g) * t

*/
//Uva 10090
int main() {
    ll n, c1, c2, n1, n2;
    while((cin >> n) && n > 0){
        cin >> c1 >> n1 >> c2 >> n2;
        ll a = n1;
        ll b = n2;
        ll c = n;
        ll x = 0, y = 0;
        ll g = euclid(a, b, x, y);
        
        if(c % g){
            cout << "failed" << ln;
            continue;
        }
        
        x *= (c / g);
        y *= (c / g);

        //rangos de la respuesta
        ll l = ceil(-(double) x / (b / g));
        ll r = floor((double) y / (a / g));
        if(l > r){
            cout << "failed" << ln;
            continue;
        }

        ll cost = c1 * b - c2 * a;
        ll x0 = 0, y0 = 0;

        if(cost * l < cost * r){
            x0 = x + (b / g) * l;
            y0 = y - (a / g) * l;
        }else{
            x0 = x + (b / g) * r;
            y0 = y - (a / g) * r;
        }
        cout << x0 << " " << y0 << ln;
    }
    return 0;
}
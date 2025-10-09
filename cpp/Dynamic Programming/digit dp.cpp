

//digit dp
//[0, a]

//What if we want [a, b]
//solve(b) - solve(a - 1)

// dado un rango contar cuando numeros hay que tengan
// la siguiente forma 22338899
// es decir, el digito en la posicion 2n-1 == 2n

const ll MOD = 1e4 + 7;

int n;
const int D = 1e5 + 5; //digitos del numero
ll dp[D][10][2][2];
short num[D];

ll add(ll a, ll b){
    return ((a % MOD) + (b % MOD)) % MOD;
}
ll sub(ll a, ll b){
    return ((a % MOD) - (b % MOD) + MOD) % MOD;
}

//prev = digito usado previamente
// eq = para saber el max_digit que puedo usar
// start = es true cuando he usado un digito diferente a cero
// (0000022) es valido porque representa el 22

ll go(int idx, int prev, bool eq, bool start){
    if(idx == n){
        return start;
    }
    ll &ans = dp[idx][prev][eq][start];
    if(ans != -1) return ans;

    ans = 0;
    int max_digit = (eq ? num[idx] : 9);

    if(idx % 2 == 0){
        //si es par puedo iniciar con cualquier digito
        for(int d = 0; d <= max_digit; d++){
            //si tengo ceros a la izq y me quedan 2 para colocar
            //solo puedo poner uno diferente  a cero
            if(!start && d == 0 && idx == n - 2) continue;

            bool new_eq = eq && d == num[idx];
            int new_start = start || (d != 0);

            if(!new_start){
                ans = add(ans, go(idx + 1, 0, new_eq, 0));
            }else{
                ans = add(ans, go(idx + 1, d, new_eq, 1));
            }
        }
    }else{
        // si es impar, tengo que poner el mismo usado anteriormente
        if(start){
            if(prev <= max_digit){
                ans = add(ans, go(idx + 1, prev, eq && prev == max_digit, 1));
            }
        }else{
            //si no he iniciado pero puedo continuar con 0s
            if(0 <= max_digit){
                ans = add(ans, go(idx + 1, 0, eq && 0 == max_digit, 0));
            }
        }
    }
    return ans;
}

string subtract_one(const string& s) {
    string res = s;
    int n = sz(res);
    int i = n - 1;

    while (i >= 0 && res[i] == '0') {
        res[i] = '9';
        i--;
    }

    if (i >= 0) {
        res[i]--;
    }

    int start = 0;
    while (start < n - 1 && res[start] == '0') {
        start++;
    }
    return res.substr(start);
}


ll solve(string &s){
    n = sz(s);
    if(sz(s) % 2 == 1){
        //en este problema la cadena
        //siempre debe ser par
        s = "0" + s;
        n = sz(s);
    }

    forn(i, n) num[i] = short(s[i] - '0');
    memset(dp, -1, sizeof dp);
    ll ans = go(0, 0, 1, 0);
    return ans;
}
int main() {
    string a, b;
    cin >> a >> b;

    string ax = subtract_one(a);
    ll aa = solve(ax);
    ll bb = solve(b);

    cout << sub(bb, aa) << ln;
    return 0;
}

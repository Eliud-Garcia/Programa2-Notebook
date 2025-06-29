
/*
    se tira un dado N veces, el dado tiene los
    numeros del 1 al 6, cual es la probabilidad
    de que la suma caiga entre [a, b]
*/

using ld = long double;

int n, a, b;
const int MAXN = 101;
ld dp[MAXN][605];
bool vis[MAXN][605];

ld go(int i, int s){
    if(i == n){
        if(s >= a && s <= b){
            return 1.0;
        }
        return 0;
    }
    if(vis[i][s]){
        return dp[i][s];
    }
    ld ans = 0;
    for(int j : {1, 2, 3, 4, 5, 6}){
        ans += (1 / 6.0) * go(i + 1, s + j);
    }
    vis[i][s] = 1;
    return dp[i][s] = ans;
}

int main() {
    cin >> n >> a >> b;
    ld ans = go(0, 0);
    printf("%.6LF\n", ans);
    return 0;
}

//teorema de la probabilidad total
// P(x) = P1 * P(x | 1) +
//        P2 * P(x | 2) +
//        P3 * P(x | 3) + ...

// Pi = probabilidad de que suceda i
// P(x | i)
//probabilidad de x dado que el evento i ya ha ocurrido

/*
    tener cuidado cuando piden
    imprimir un numero flotante
    con (rounding half to even)
    usar python para no tener
    problemas de precision
*/

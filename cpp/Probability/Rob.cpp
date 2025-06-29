

/*
    hay N bancos y se quiere robar
    la maxima cantidad de dinero posible

    limit = prob tolerable de ser atrapado.

    si decide robar el banco i
    roba money[i] dinero
    hay prob p[i] de ser atrapado


    todas las prob son independientes.

*/

int n;
double limit;
const int MAXN = 105;

int money[MAXN];
double p[MAXN];

double dp[100 * 100 + 5];

int main() {
    cin >> limit >> n;
    int total = 0;
    forn(i, n) {
        cin >> money[i] >> p[i];
        total += money[i];
    }
    memset(dp, 0, sizeof dp);
    dp[0] = 1.0; //max prob de robar 0 de dinero sin ser capturado
    forn(i, n) {
        for(int val = total; val >= 0; val--) {
            //maximizar la probabilidad de NO ser atrapado
            if(val - money[i] >= 0) {
                dp[val] = max(dp[val], dp[val - money[i]] * (1.0 - p[i]));
            }
        }
    }
    int ans = 0;
    for(int val = total; val >= 0; val--) {
        //prob de ser atrapado
        if(1.0 - dp[val] < limit) {
            ans = val;
            break;
        }
    }
    cout << ans << ln;

    return 0;
}


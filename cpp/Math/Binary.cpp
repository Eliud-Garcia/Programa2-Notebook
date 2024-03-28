
//numeros desde [0, n] en binario
vi pre(int n){
    vi bin;
    bin.pb(0);
    forab(i, 1, n + 1){
        int j = 32;
        int x = i;
        string s;
        bool turn = 0;
        while(j--){
            int bit = (x >> j) & 1;
            if(bit) turn = 1;
            if(turn){
                s+= (bit ? "1" : "0");
            }
        }
        int X = stoi(s);
        bin.pb(X);
    }
    return bin;
}
//dado un N decir si se puede formar
//por la multiplicacion de numeros
//en su representacion binaria
//N = bin * bin
//121 = 11 * 11
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin >> t;
    vi bin = pre(32);
    int MAX = 1e5 + 10;
    vb sol(MAX, 0);
    sol[1] = 1;
    forab(i, 1, MAX){
        if(sol[i]){
            for(int x : bin){
                if((ll) i * x < MAX) sol[i*x] = 1;
            }
        }
    }
    while(t--){
        ll n; cin >> n;
        cout << (sol[n] ? "YES" :"NO" ) <<ln;
    }   
    return 0;
}
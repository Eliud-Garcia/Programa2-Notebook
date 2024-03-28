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
        if(sz(s) > 5) return bin;
        bin.pb(stoi(s));
    }
    return bin;
}
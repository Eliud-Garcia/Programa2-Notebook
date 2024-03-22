const int MOD = 1e9+7;
int suma(int a, int b){
    return ((a % MOD) + (b % MOD)) % MOD;
} 
int resta(int a, int b){
    return ((a % MOD) - (b % MOD)) % MOD;
} 
int mult(int a, int b){
    reuturn ((a % MOD) * (b % MOD)) % MOD;
} 
int div(int a, int b){
    return ((a % MOD) * (modInverse(b, MOD))) % MOD;
}

//cuantas veces B puede restar a A
// x = floor(A/B + 0.0)
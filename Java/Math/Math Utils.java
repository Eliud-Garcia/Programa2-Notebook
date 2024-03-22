//Modular arithmetic
int MOD = (int)1e9+7;
int suma(int a, int b){
    return ((a % MOD) + (b % MOD)) % MOD;
} 
int resta(int a, int b){
    return ((a % MOD) - (b % MOD)) % MOD;
} 
int mult(int a, int b){
    return ((a % MOD) * (b % MOD)) % MOD;
} 
int div(int a, int b){
    return ((a % MOD) * (modInverse(b, MOD))) % MOD;
}

//GCD    
static long gcd(long a, long b) {
    return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
}
//LCM
static long lcm(long a, long b) {
    long lcm = (a / gcd(a, b)) * b;
    return lcm > 0 ? lcm : -lcm;
}

//cuantas veces B puede restar a A
// x = floor(A/B + 0.0)
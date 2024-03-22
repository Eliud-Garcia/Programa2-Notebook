const int MOD = 1e9+7;
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
ll gcd(ll a, ll b) {
    return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
}
//LCM
ll lcm(ll a, ll b) {
    long lcm = (a / gcd(a, b)) * b;
    return lcm > 0 ? lcm : -lcm;
}
//cuantas veces B puede restar a A
// x = floor(A/B + 0.0)
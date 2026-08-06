//hash monoide
using i128 = __int128;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll MOD = 2305843009213693951LL; // modulo 2^61- 1
const ll B = uniform_int_distribution<ll>(MOD / 10, MOD - MOD / 10)(rng);
inline ll mulmod(ll a, ll b) { return (ll)((i128)a * b % MOD); } 
 
struct UnitHash {
    ll h, b;
    UnitHash() : h(0), b(1) {} // neutro ""
    UnitHash(ll h_, ll b_) : h(h_), b(b_) {}
};
// concatenacion: s seguido de t
UnitHash operator*(const UnitHash& s, const UnitHash& t) {
    return UnitHash((s.h + mulmod(s.b, t.h)) % MOD, mulmod(s.b, t.b));
}
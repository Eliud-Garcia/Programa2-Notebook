
//max subarray sum
ll kadane(vll &a, int l, int r){
    ll mx = 0LL;
    ll cur = 0LL;
    for(int i = l; i < r; i++){
        cur = max(cur + a[i], a[i]);
        mx = max(mx, cur);
    }
    return mx;
}


//arr[0] es ignorado
vi arr = {0, 1, 6, 4, 2, 5, 3 };
int n = arr.size();
vll pf(n + 1, 0);
forab (i, 1, n + 1) {
    pf[i] = pf[i - 1] + arr[i];
}
//query en rango desde a hasta b
// a va desde 1 hasta n
// b va desde 1 hasta n
//[a, b] inclusive
int a = 2;
int b = 6;
ll query = pf[b] - pf[a - 1];
cout << query << ln;
    
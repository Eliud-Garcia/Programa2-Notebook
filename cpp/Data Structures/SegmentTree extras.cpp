

/*
oper = a + b
obtener el k-esimo 1 o lower_bound
inicializar con 1s el vector
*/
int find_kth(int v, int tl, int tr, int k) {
    if (k > st[v])
        return -1;
    if (tl == tr)
        return tl;
    int tm = (tl + tr) / 2;
    if (st[L(v)] >= k)
        return find_kth(L(v), tl, tm, k);
    else
        return find_kth(R(v), tm + 1, tr, k - st[L(v)]);
}
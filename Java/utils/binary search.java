
//elemento que es >= x
static int lower_bound(List<Long> a, long x) {
    int l = -1, r = a.size();
    while (l + 1 < r) {
        int m = (l + r) >>> 1;
        if (a.get(m) >= x)
            r = m;
        else
            l = m;
    }
    return r;
}

//elemento que es > x
static int upper_bound(List<Long> a, long x) {
    int l = -1, r = a.size();
    while (l + 1 < r) {
        int m = (l + r) >>> 1;
        if(a.get(m) <= x)
            l = m;
        else
            r = m;
    }
    return l + 1;
}

// elemento mayor de arr que es <= x
static int search(int l, int r, int x, int arr[]){
    int res = -1;
    while(l <= r){
        int mid = l + (r - l)/2;
        if(x>=arr[mid]){
            res = mid;
            l = mid + 1; 
        }
        if( x < arr[mid]){
            r = mid -1 ;
        } 
    }
    return res;
}
//busqueda binaria sobre la respuesta 
//usando valores double
double l = 0, r = 1e9, mid;
int it = 100;
while (it-- > 0) {
    mid = l + (r - l) / 2;
    //cambiar check por lo necesitado
    if (check(a, k, mid)) {
        l = mid;
    } else {
        r = mid;
    }
}
sa.printf("%.7f\n", l);
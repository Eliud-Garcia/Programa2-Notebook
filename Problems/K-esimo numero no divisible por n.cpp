
/*
decir el k-esimo numero que no es divisible por n
Ejemplo:
n = 3, k = 7;
                      1  2  3  4  5  6   7   8   9
no divisibles por n = 1, 2, 4, 5, 7, 8, 10, 11, 13
*/
int n, k;
cin >> n >> k;
int need = (k - 1) / (n - 1);
cout << k + need << ln;

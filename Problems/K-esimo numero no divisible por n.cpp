#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define ll long long
#define forn(i, n) for (int i = 0; i < n; i++)

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
	cin >> t;
	while (t--) {
		int n, k;
        //decir el k-esimo numero que no es divisible por n
        /*
            Ejemplo: 
            n = 3, k = 7;
                                  1  2  3  4  5  6   7   8   9
            no divisibles por n = 1, 2, 4, 5, 7, 8, 10, 11, 13
        */
		cin >> n >> k;
		int need = (k - 1) / (n - 1);
		cout << k + need << ln;
	}

    return 0;
}
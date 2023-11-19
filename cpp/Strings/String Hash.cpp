#include <bits/stdc++.h>
using namespace std;
#define endl     '\n' 
#define sz(x)    int((x).size())
#define forn(i, n) for (int i = 0; i < n; ++i)


/*
hash_table
sirve para contar cuantas veces aparece un patron en un string
en un rango [l,r] en O(1) con O(n) de preprocesamiento
ejemplo:
string s;
a b a c a b a d a b a c a b a
string p;
b a
hash_table<int> h(s,p);
0 0 1 1 1 1 2 2 2 2 3 3 3 3 4

hash_table(string s, int m)
sirve para contar cuantas veces aparece un patron de longitud m en un string
modificar bulid() segun condicion 

*/


template<typename T>
struct hash_table
{
    string s, p;
    int n, m;
    vector<T>prefix;
    hash_table(string s, string p) {
        this->s = s;
        this->p = p;
        this->n = sz(s);
        this->m = sz(p);
        prefix.resize(n + 5, 0);
        build();
    }
    hash_table(string s, int m) {
        this->s = s;
        this->n = sz(s);
        this->m = m;
        prefix.resize(n + 5, 0);
        build();
    }

    void build() {
        forn(i, n - m + 1) {
            int ok = 1;
            forn(j, m) {
                if (s[i + j] != p[j]) {
                    ok = 0;
                    break;
                }
            }
            prefix[i + 1] = prefix[i] + ok;
        }
    }
    int query(int l, int r) {
        if (r - l + 1 < m) return 0;
        return prefix[r - m + 1] - prefix[l - 1];
    }
};
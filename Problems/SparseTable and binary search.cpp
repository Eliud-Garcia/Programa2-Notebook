

/*
    buscando el siguiente menor con
    sparse table y busqueda binaria
    https://codeforces.com/gym/104603/problem/A
*/

#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

struct STable {
    int n, K;
    vector<vector<pair<int, int>>> st;

    STable(const vector<pair<int, int>>& a)
    {
        n = int(a.size());
        K = int(log2(n)) + 1;
        st.assign(n + 1, vector<pair<int, int>>(K));
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];
        for (int j = 0; j < K - 1; j++)
            for (int i = 0; i + (1 << (j + 1)) <= n; ++i)
                st[i][j + 1] = oper(st[i][j], st[i + (1 << j)][j]);
    }

    pair<int, int> oper(pair<int, int>& a, pair<int, int>& b)
    {
        return min(a, b);
    }

    pair<int, int> query(int l, int r)
    {
        int k = 31 - __builtin_clz(r - l + 1);
        return oper(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

pair<int, int> search(int l, int r, int candy, STable& st)
{
    pair<int, int> ans = { (int)1e9 + 10, -1 };
    while (l <= r) {
        int mid = l + (r - l) / 2;
        pair<int, int> left = st.query(l, mid);
        pair<int, int> right = st.query(mid, r);

        if (left.first <= candy) {
            ans = left;
            r = mid - 1;
        } else if (left.first > candy) {
            l = mid + 1;
        } else if (right.first <= candy) {
            l = mid + 1;
            ans = right;
        } else if (right.first > candy) {
            r = mid - 1;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> viaje(n);
    for (int i = 0; i < n; i++) {
        cin >> viaje[i];
    }
    vector<pair<int, int>> empleados(m);
    for (int i = 0; i < m; i++) {
        int e;
        cin >> e;
        empleados[i] = { e, i };
    }

    STable st = STable(empleados);
    for (int i = 0; i < n; i++) {
        int candy = viaje[i];
        int l = 0;
        int r = m - 1;
        while (true) {
            pair<int, int> ans;
            ans = search(l, r, candy, st);
            if (ans.first > candy) {
                break;
            }
            candy = (candy % ans.first);
            if (candy == 0) {
                break;
            }
            l = ans.second + 1;
            if (l >= m) {
                break;
            }
        }
        cout << candy << " ";
    }
}
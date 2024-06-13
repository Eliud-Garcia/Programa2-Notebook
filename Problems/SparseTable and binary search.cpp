
typedef pair<int, int> ii;

/*
buscando el siguiente menor con
sparse table y busqueda binaria
https://codeforces.com/gym/104603/problem/A
*/

struct STable {
  int n, K;
  vector<vector<ii>> st;
  STable(const vector<ii>& a) {
    n = int(a.size());
    K = int(log2(n)) + 1;
    st.assign(n + 1, vector<ii>(K));
    forn (i, n)
    st[i][0] = a[i];
    forn (j, K - 1)
    for (int i = 0; i + (1 << (j + 1)) <= n; ++i)
      st[i][j + 1] = oper(st[i][j], st[i + (1 << j)][j]);
  }

  ii oper(ii &a, ii &b) {
    return min(a, b);
  }

  ii query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return oper(st[l][k], st[r - (1 << k) + 1][k]);
  }
};

ii search(int l, int r, int candy, STable& st) {
  ii ans = {1e9 + 10, -1};
  while (l <= r) {
    int mid = l + (r - l) / 2;
    ii left = st.query(l, mid);
    ii right = st.query(mid, r);

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

int main() {
  int n, m;
  cin >> n >> m;
  vi viaje(n);
  forn(i, n) {
    cin >> viaje[i];
  }
  vector<ii> empleados(m);
  forn(i, m) {
    int e;
    cin >> e;
    empleados[i] = { e, i };
  }
  STable st = STable(empleados);
  forn (i, n) {
    int candy = viaje[i];
    int l = 0;
    int r = m - 1;
    while (true) {
      ii ans;
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

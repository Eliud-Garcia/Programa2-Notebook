
// [1, n]
//
template <typename T>
struct ft_range {
  vector<T> ft1, ft2;

  ft_range(int n) {
    ft1.assign(n + 1, 0);
    ft2.assign(n + 1, 0);
  }

  ft_range(vector<T> &a) : ft1(sz(a) + 1), ft2(sz(a) + 1){
    forab(i, 1, sz(a) + 1)
      update(i, i, a[i]);
  }

  T query(vector<T> & ft, int i) {
    T sum = 0;
    for(; i; i -= (i & -i)) sum += ft[i];
    return sum;
  }
  void update(vector<T> & ft, int i, int v) {
    for(; i < sz(ft); i += (i & -i))
      ft[i] += v;
  }
  void update(int i, int j, T v) {
    update(ft1, i, v);
    update(ft1, j + 1, -v);
    update(ft2, i, v * (i - 1));
    update(ft2, j + 1, -v * j);
  }
  T query(int i) {
    return query(ft1, i) * i - query(ft2, i);
  }
  T query(int i, int j) {
    return query(j) - query(i - 1);
  }
};

int main() {
  int n; cin >> n;
  vector<int> v(n + 1);
  forab(i, 1, n + 1) cin >> v[i];
  ft_range<int> bit(v);
	int q;
	cin >> q;
	int l, r, val;
	while(q--){
    char op;
		cin >> op;
		if(op == 'q'){
			cin >> l >> r;
			cout << bit.query(l, r) << ln;
		}else{
			cin >> l >> r >> val;
			bit.update(l, r, val);
		}
	}
  return 0;
}


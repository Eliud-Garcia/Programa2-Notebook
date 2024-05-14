
typedef pair<int, int> pii;

bool cmp(pii &a, pii &b) {
  if(a.second == b.second) return a.first < b.first;
  return a.second > b.second;
}

//for set
set<pii, decltype(&cmp)> q(&cmp);


//funciones dentro del main
function<ll(int, int, int)> suma = [&](int a, int b, int c) {
  return ll(a + b + c);
};

cout << suma(11, 11, 1) << ln;

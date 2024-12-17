
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

//input / output
string x;
getline(cin, x);//lee linea completa

//imprime long double con 6 decimales
printf("%.6LF\n", value);//long double

//impimir string con printf
string aux = "texto";
printf("%s\n", aux.c_str());




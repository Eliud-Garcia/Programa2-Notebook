//String completa a miniscula
transform(all(in), in.begin(), ::tolower);


//A es subsecuencia de B?
bool is_subsecuence(vi &a, vi &b){
  int at = 0;
  for(auto i: b){
    if(i == a[at]) at++;
    if(at == sz(a)) return 1;
  }
  return 0;
}
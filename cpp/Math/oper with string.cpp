//multiply big numbers
string multyply(string a, int b){
  int carry = 0;
  string ans = "";
  forn(i, sz(a)){
    carry = ((a[i] - '0') * b + carry);
    ans += carry % 10 + '0';
    carry /= 10;
  }
  while(carry != 0){
    ans += carry % 10  + '0';
    carry /= 10;
  }
  return ans;
}

string res = "1";
for(auto [p, ex] : fac){
  forn(i, ex){
    res = multyply(res, p);
  }
}
reverse(all(res));
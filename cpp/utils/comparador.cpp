
typedef pair<int, int> pii;

bool cmp(pii a, pii b){
  if(a.second == b.second) return a.first < b.first;
  return a.second > b.second;
}

//for set
set<pii, decltype(&cmp)> q(&cmp);
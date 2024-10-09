
//O(n)
const int MAXN = 10000000;
int lp[MAXN + 1]; //minimo factor primo
vi pr;

void cribaLineal(){
  for (int i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j= 0; j < sz(pr) && pr[j] <= lp[i] && i * pr[j] <= MAXN; ++j)
      lp[i * pr[j]] = pr[j];
  }
}
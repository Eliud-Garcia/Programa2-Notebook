#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define forn(i, n) for(int i = 0; i < n; i++)
#define forab(i, a, b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;


//shortest path
const ll oo = 1e18 + 5;
struct Edge {
  int a, b, cost;
};
int n, m;

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  vector<Edge> edges(m);
  int a, b, c;
  forn(i, m){
    cin >> a >> b >> c;
    edges[i] = {a, b, c};
  }
  int source = 1;
  int dest = n;
  vll d(n + 1, oo);//distancia
  vi p(n + 1,  -1);//parent
  d[source] = 0;
  forn (i, n - 1){
    for (Edge e : edges){
      if (d[e.a] < oo){
        d[e.b] = min(d[e.b], d[e.a] + e.cost);
        p[e.b] = e.a;
      }
    }
  }
  if (d[dest] == oo){
    //no hay camino desde source hasta dest
  }else{
    cout <<"distancia minima = "<< d[dest] << ln;
    vi path;
    for (int cur = dest; cur != -1; cur = p[cur])
      path.pb(cur);
    reverse(all(path));
    for (int u : path)
      cout << u << ' ';
  }
  return 0;
}

/*#################*/

//negative cycle
  int source = 1;
  vll d(n + 1, oo); //dist
  vi p(n + 1, -1); //parent
  d[source] = 0;
  int x;
  forn (i, n) {
    x = -1;
    for (Edge e : edges)
      if (d[e.a] < oo)
        if (d[e.b] > d[e.a] + e.cost) {
          d[e.b] = max(-oo, d[e.a] + e.cost);
          p[e.b] = e.a;
          x = e.b;
        }
  }
  if (x == -1){
    //no hay ciclo negativo desde source
  }else {
    int y = x;
    forn (i, n)
      y = p[y];
    vi path;
    for (int cur = y;; cur = p[cur]) {
      path.pb(cur);
      if (cur == y && path.size() > 1)
        break;
    }
    reverse(all(path));
    cout << "Negative cycle: ";
    for (int u : path)
      cout << u << ' ';
  }
  
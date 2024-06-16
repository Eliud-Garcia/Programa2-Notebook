//find shortest path from A to B
int n, m;
const int MAXN = 1002;
char grid[MAXN][MAXN];

//der, abajo, izq, arriba
vi dx = {0, 1, 0, -1};
vi dy = {1, 0, -1, 0};

bool valid(int i, int j) {
  if(i < 0 || i >= n || j < 0 || j >= m) {
    return 0;
  }
  if(grid[i][j] == '#') return 0;
  return 1;
}
string path;
bool bfs(int i, int j) {
  queue<array<int, 3>> q;
  vector<vb> vis(n, vb(m, 0));
  char br[n][m];
  q.push({i, j, 0});
  vis[i][j] = 1;

  while(sz(q)) {
    auto &[x, y, dis] = q.front(); q.pop();
    if(grid[x][y] == 'B') { //found
      while(true){ //build path
        path.pb(br[x][y]);
        if(path.back() == 'R') y--;
        if(path.back() == 'D') x--;
        if(path.back() == 'L') y++;
        if(path.back() == 'U') x++;
        if(x == i && y == j) break;
        if(!valid(x, y)) break;
      }
      return 1;
    }

    forn(k, 4) { // dir
      int nx = x + dx[k];
      int ny = y + dy[k];
      if(valid(nx, ny) && !vis[nx][ny]) {
        if(k == 0) br[nx][ny] = 'R';
        if(k == 1) br[nx][ny] = 'D';
        if(k == 2) br[nx][ny] = 'L';
        if(k == 3) br[nx][ny] = 'U';
        vis[nx][ny] = 1;
        q.push({nx, ny, dis + 1});
      }
    }
  }
  return 0;
}
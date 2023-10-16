


	/*
     *    https://cses.fi/problemset/task/1193/
     *    un mapa en forma de matriz, llegar desde A hasta B
     */

    static boolean vis[][];
    static char grid[][];
    static char br[][];
    static Deque<Character> path = new LinkedList<>();
    static int n, m;

    static boolean isValid(int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= m){
            return false;
        }
        if (grid[r][c] == '#' || vis[r][c]){
            return false;
        }
        return true;
    }

    static boolean bfs(int x, int y) {
        Deque<int[]> q = new LinkedList<>();
        q.add(new int[] { x, y });
        vis[x][y] = true;

        while (!q.isEmpty()) {
            int i = q.peek()[0];
            int j = q.peek()[1];
            q.removeFirst();
            if (grid[i][j] == 'B') {
                while (true) {
                    path.add(br[i][j]);
                    if (path.getLast() == 'L')
                        j++;
                    if (path.getLast() == 'R')
                        j--;
                    if (path.getLast() == 'U')
                        i++;
                    if (path.getLast() == 'D')
                        i--;
                    if (i == x && j == y)
                        break;

                    if (i < 0 || i >= n || j < 0 || j >= m)
                        break;
                }
                return true;
            }
            // left
            if (isValid(i, j - 1)) {
                br[i][j - 1] = 'L';
                q.add(new int[] { i, j - 1 });
                vis[i][j - 1] = true;
            }

            // right
            if (isValid(i, j + 1)) {
                br[i][j + 1] = 'R';
                q.add(new int[] { i, j + 1 });
                vis[i][j + 1] = true;
            }

            // up
            if (isValid(i - 1, j)) {
                br[i - 1][j] = 'U';
                q.add(new int[] { i - 1, j });
                vis[i - 1][j] = true;
            }

            // down
            if (isValid(i + 1, j)) {
                br[i + 1][j] = 'D';
                q.add(new int[] { i + 1, j });
                vis[i + 1][j] = true;
            }

        }
        return false;

    }

    public static void main(String[] args) throws IOException {
        n = nextInt();
        m = nextInt();
        grid = new char[n][m];
        vis = new boolean[n][m];
        br = new char[n][m];
        int x= -1, y = -1;
        for (int i = 0; i < n; i++) {
            String line = next();
            for (int j = 0; j < line.length(); j++) {
                grid[i][j] = line.charAt(j);
                if(grid[i][j]=='A'){
                    x = i;
                    y = j;
                }
            }
        }
        if(bfs(x, y)){
            sa.println("YES");
            sa.println(path.size());
            while(!path.isEmpty()){
                sa.print(path.removeLast());
            }
            sa.println();
            
        }else{
            sa.println("NO");
        }

        sa.close();
    }

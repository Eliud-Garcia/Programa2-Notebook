
import java.io.*;
import java.util.*;

public class BFS_matriz {

    static FastWriter sa = new FastWriter();
    static InputReader en = new InputReader();

    /*
     *    https://cses.fi/problemset/task/1193/
     *    un mapa en forma de matriz, llegar desde A hasta B
     */
    static class pair<T> {
        T first;
        T second;
        public pair(T f, T s) {
            first = f;
            second = s;
        }
    }

    static final int MAX_N = 1001;
    static boolean vis[][] = new boolean[MAX_N][MAX_N];
    static char ar[][] = new char[MAX_N][MAX_N];
    static char br[][] = new char[MAX_N][MAX_N];
    static LinkedList<Character> path = new LinkedList<>();
    static int n, m;
    
    static boolean isValid(int x, int y) {
        if (x < 1 || x > n || y < 1 || y > m) return false;
        if (ar[x][y] == '#' || vis[x][y]==true) return false;
        return true;
    }
    
    static boolean bfs(int x, int y) {
        LinkedList<pair<Integer>> q = new LinkedList<>();
        q.add(new pair<Integer>(x, y));
        vis[x][y] = true;

        while (!q.isEmpty()) {
            int a = q.getFirst().first;
            int b = q.getFirst().second;
            q.removeFirst();
            if(ar[a][b] == 'B'){
                while(true){
                    path.add(br[a][b]);
                    if(path.getLast() == 'L') b++;
                    if(path.getLast() == 'R') b--;
                    if(path.getLast() == 'U') a++;
                    if(path.getLast() == 'D') a--;

                    if(a==x && b==y) break;
                }
                return true;
            }
            //left
		    if(isValid(a , b - 1)){
                br[a][b-1] = 'L';
                q.add(new pair<Integer>(a, b-1));
                vis[a][b-1] = true;
            } 
		
		    //right
		    if(isValid(a , b + 1)){
                br[a][b+1] = 'R';
                q.add(new pair<Integer>(a, b+1));
                vis[a][b+1] = true;
            } 
		
		    //up
		    if(isValid(a - 1, b)) {
                br[a - 1][b] = 'U';
                q.add(new pair<Integer>(a-1, b));
                vis[a-1][b] = true;
            }
            
		
		    //down
		    if(isValid(a + 1, b)){
                br[a + 1][b] = 'D';
                q.add(new pair<Integer>(a+1, b));
                vis[a+1][b] = true;
            } 

        }
        return false;

    }

    static void solve() throws IOException {
        n = en.nextInt();
        m = en.nextInt();

        int x= 0, y= 0;
        for (int i = 1; i <= n; i++) {
            String line = en.next();
            for (int j = 1; j <= m; j++) {
                ar[i][j] =line.charAt(j-1);
                if(ar[i][j]=='A') {
                    x=i;
                    y=j;
                }
            }
        }
        if(bfs(x, y)){
            sa.println("YES\n"+path.size());
            StringBuilder ans = new StringBuilder();
            while(!path.isEmpty()) ans.append(path.removeLast());
            sa.println(ans);
        }else sa.println("NO");
        
    }

    public static void main(String[] args) throws IOException {
        long t;
        t = 1;
        while (t-- > 0) {
            solve();
        }
        sa.close();

    }

    

}
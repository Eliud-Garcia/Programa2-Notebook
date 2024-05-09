import java.io.*;
import java.util.*;
import static java.lang.Math.*;
public class Main {
    public static void main(String[] args) throws IOException {
        //en = new BufferedReader(new FileReader("in.txt"));
        //sa = new PrintWriter(new BufferedWriter(new FileWriter("out.txt")));
        
        while(input()){
            int n = nextInt();
            if(n == 0) break;
            sa.print(n+"\n");
        }

        sa.close();
    }

    static boolean input(){
        String s;
        boolean ok = false;
        try{
            s = en.readLine();
            sten = new StringTokenizer(s);
            ok = !(s.isBlank());
        }catch(Exception e){}
        return ok;
    }

    static String next(){
        while (sten == null || !sten.hasMoreElements()) {
            try { sten = new StringTokenizer(en.readLine());}
            catch (Exception e) {e.printStackTrace();}
        }
        return sten.nextToken();
    }
    static int nextInt(){
        return Integer.parseInt(next());
    }
    static long nextLong(){
        return Long.parseLong(next());
    }
    static double nextDouble(){
        return Double.parseDouble(next());
    }
    static PrintWriter sa = new PrintWriter(new OutputStreamWriter(System.out));
    static BufferedReader en = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer sten;
}
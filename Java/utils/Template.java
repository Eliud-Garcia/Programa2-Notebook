import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class Main {
    public static void main(String[] args)  {
        //code here
        sa.close();
    }
    static String next()  {
        while (st == null || !st.hasMoreElements()) {
            try{ st = new StringTokenizer(en.readLine());}
            catch(Exception e){e.printStackTrace();}
        }
        return st.nextToken();
    }
    static String nextLine(){
        String str = "";
        try{str = en.readLine();}
        catch(Exception e){e.printStackTrace();}
        return str;
    }
    static int nextInt(){
        return Integer.parseInt(next());
    }
    static long nextLong() {
        return Long.parseLong(next());
    }
    static double nextDouble(){
        return Double.parseDouble(next());
    }
    static PrintWriter sa = new PrintWriter(new OutputStreamWriter(System.out));
    static BufferedReader en = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
}
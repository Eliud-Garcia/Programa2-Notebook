import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class Template {

    static PrintWriter sa = new PrintWriter(new OutputStreamWriter(System.out));
    static BufferedReader en = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    
    
    
    public static void main(String[] args) throws IOException {
        //code here
    }
    
   
    
    

    static String next() throws IOException {
        while (st == null || !st.hasMoreElements()) {
            st = new StringTokenizer(en.readLine());
        }
        return st.nextToken();
    }
    
    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    static long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    static String nextLine() throws IOException {
        String str = "";
        str = en.readLine();
        return str;
    }

}
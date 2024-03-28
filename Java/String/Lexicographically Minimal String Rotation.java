// Lyndon Factorization
/*
* The problem:
* Given a string S of size N
* A right-rotation is that move the leftmost character to rightmost of S
* Find the least right-rotation to make S
* become the smallest lexicographical ordered string
*/
// https://codeforces.com/blog/entry/90035#duval
// devuelve el indice donde comienza la rotación 
//lexicograficamente menor de s.
    static int minimum_expression(String s) {
        s = s + s; // si no se concatena devuelve el indice del sufijo menor
        int len = s.length(), i = 0, j = 1, k = 0;
        while (i + k < len && j + k < len) {
            if (s.charAt(i + k) == s.charAt(j + k))
                k++;
            else if (s.charAt(i + k) > s.charAt(j + k)) {
                i = i + k + 1;
                k = 0; // cambiar por < para maximum
            } else {
                j = j + k + 1;
                k = 0;
            }
            if (i == j)
                j++;
        }
        return min(i, j);
    }

    public static void main(String[] args) throws IOException {
        String s = next();
        int n = s.length();
        int i = minimum_expression(s);
        StringBuilder ans = new StringBuilder();
        int cnt = 0;
        while (cnt < n) {
            ans.append(s.charAt(i));
            i++;
            i%=n;
            cnt++;
        }
        sa.println(ans);
        sa.close();
    }

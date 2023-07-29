

 // usar prefix function
// cuenta las veces que p aparece en s

    static int kmp(String s, String p) {
        int n = s.length(), m = p.length(), cnt = 0;
        int pf[] = prefix_function(p);
        for (int i = 0, j = 0; i < n; i++) {
            while (j > 0 && s.charAt(i) != p.charAt(j)) j = pf[j - 1];
            if (s.charAt(i) == p.charAt(j)) j++;
            if (j == m) {
                cnt++;
                j = pf[j - 1];
            }
        }
        return cnt;

    }

static int[] prefix_function(String s) {
    int n = s.length();
    int pf[] = new int[n];
    pf[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s.charAt(i) != s.charAt(j)) j = pf[j - 1];
        if (s.charAt(i) == s.charAt(j))
            j++;
        pf[i] = j;
    }
    return pf;
}
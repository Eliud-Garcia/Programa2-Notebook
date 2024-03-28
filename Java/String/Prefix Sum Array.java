 /* letter frecuency in a range */
static void PrefixSumArray(String s) {
    int psa[][] = new int[26][s.length() + 1];
    for (int i = 1; i <= s.length(); i++) {
        for (int j = 0; j < 26; j++) {
            psa[j][i] = psa[j][i - 1];
        }
        char cur = s.charAt(i - 1);
        psa[cur - 'a'][i]++;
    }
    char c = 'e';
    int left = 1, right = s.length();
    sa.println(psa[c - 'a'][right] - psa[c - 'a'][left - 1]);
}
//retorna los indices en los que empieza una ocurrencia
//los indices van desde 1
static List<Integer> rabin_karp(String pattern, String text) {
    int p = 31;
    int m = (int) 1e9 + 9;
    int S = pattern.length(), T = text.length();

    long p_pow[] = new long[max(S, T)];
    p_pow[0] = 1;
    for (int i = 1; i < (int) p_pow.length; i++) {
        p_pow[i] = (p_pow[i - 1] * p) % m;
    }

    long h[] = new long[T + 1];
    for (int i = 0; i < T; i++) {
        h[i + 1] = (h[i] + (text.charAt(i) - 'a' + 1) * p_pow[i]) % m;
    }
    long h_s = 0;
    for (int i = 0; i < S; i++) {
        h_s = (h_s + (pattern.charAt(i) - 'a' + 1) * p_pow[i]) % m;
    }

    List<Integer> occurences = new ArrayList<>();
    for (int i = 0; i + S - 1 < T; i++) {
        long cur_h = (h[i + S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m){
            occurences.add(i);
        }
    }
    return occurences;
}
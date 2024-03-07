static class str_hash {
    long c, mod;
    long[] h, p;

    //cx = 131
    //modx = 1e9 + 7
    str_hash(String s, long cx, long modx) {
        c = cx;
        mod = modx;
        int n = s.length();
        p = new long[n + 1];
        h = new long[n + 1];
        p[0] = 1;
        h[0] = 0;
        for (int i = 0; i < n; i++) {
            h[i + 1] = (c * h[i] + s.charAt(i)) % mod;
            p[i + 1] = (c * p[i]) % mod;
        }
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    long get(int a, int b) {//[a, b] desde 0
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
    }
}

 //binaria sobre el Hash
 static int bs(List<Long> a, long x) {
    int l = 0;
    int r = a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (a.get(mid) == x) {
            return mid;
        }
        if (a.get(mid) > x) {
            r = mid - 1;
        }
        if (a.get(mid) < x) {
            l = mid + 1;
        }
    }
    return -1;
}

public static void main(String[] args){
    String a = next();
    String b = next();
    long mod = (long) 1e9 + 7;
    str_hash aa = new str_hash(a, 131, mod);
    str_hash bb = new str_hash(b, 131, mod);

    //se genera el hash de todas las subcadenas de B
    List<Long> hashB = new ArrayList<>();
    for (int i = 0; i < b.length(); i++) {
        for(int k = 1; i + k <= b.length(); k++){
            long hash = bb.get(i, i + k - 1);
            hashB.add(hash);
        }
    }
    Collections.sort(hashB);//ordenar para la binaria
    int n = a.length();
    long ans = (int) 1e9;
    
    //se valida si una subcadena de A de tamaño K no aparece en B
    for (int i = 0; i < n; i++) {
        for(int k = 1; i + k <= n; k++){
            long hash = aa.get(i, i + k - 1);
            int idx = bs(hashB, hash);
            if(idx < 0){
                ans = min(ans, k);
            }
        }
    }
    sa.print((ans == (int) 1e9 ? -1: ans)+"\n");
    sa.close();
}
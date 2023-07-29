



static int N = 1000 * 1000;
    static int nxt[][] = new int[N][26];
    static boolean end[] = new boolean[N];
    static int cnt[] = new int[N];
    static int nodes = 1;

    // agregar = 1
    // eliminar = -1
    static void add_remove(String s, int op) {
        int cur = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int v = c - 'a';
            if (nxt[cur][v] == 0) {
                nxt[cur][v] = nodes;
                nodes++;
            }
            cur = nxt[cur][v];
            cnt[cur] += op;
        }
        if (op == 1)
            end[cur] = true;
        else
            end[cur] = false;
    }

    static boolean find(String s) {
        int cur = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int v = c - 'a';
            if (nxt[cur][v] == 0) {
                return false;
            }
            cur = nxt[cur][v];
            if (cnt[cur] == 0)
                return false;
        }
        if (end[cur])
            return true;
        else
            return false;
    }

    // cantidad de palabras agregadas que inician con s
    static int count(String s) {
        int cur = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int v = c - 'a';
            if (nxt[cur][v] == 0) {
                return 0;
            }
            cur = nxt[cur][v];
        }
        return cnt[cur];
    }

    static void solve() throws IOException {

        int q = en.nextInt();
        while (q-- > 0) {
            String w = en.next();
            String s = en.next();
            if (w.equals("add")) {
                add_remove(s, 1);
            } else if (w.equals("remove")) {
                add_remove(s, -1);
            } else if (w.equals("query")) {
                sa.println(find(s) ? "YES" : "NO");
            } else {
                sa.println(count(s));
            }
        }

        /*
         * input
         * 
         * 11
         * add toy
         * add tea
         * add ted
         * add a
         * add ten
         * add in
         * add inner
         * c t
         * c te
         * c in
         * c taxi
         */

        /*
         * output
         * 4
         * 3
         * 2
         * 0
         */
    }
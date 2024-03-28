//AhoCorasick 
static class node {
    int child[];
    int p;
    char c;
    int suffixLink;
    int endLink;
    int id;
    node(int p, char c) {
        this.p = p;
        this.c = c;
        this.child = new int[26];
        Arrays.fill(child, -1);
        this.suffixLink = -1;
        this.endLink = -1;
        this.id = -1;
    }
}

static class AhoCorasick {
    ArrayList<node> t;
    ArrayList<Integer> lengths;
    int wordCount;
    AhoCorasick() {
        t = new ArrayList<>();
        t.add(new node(-1, (char) 0));
        lengths = new ArrayList<>();
        wordCount = 0;
    }
    void add(String s) {
        int u = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int idx = c - 'a';
            if (t.get(u).child[idx] == -1) {
                t.get(u).child[idx] = t.size();
                t.add(new node(u, c));
            }
            u = t.get(u).child[idx];
        }
        t.get(u).id = wordCount++;
        lengths.add(s.length());
    }

    void link(int u) {
        if (u == 0) {
            t.get(u).suffixLink = 0;
            t.get(u).endLink = 0;
            return;
        }
        if (t.get(u).p == 0) {
            t.get(u).suffixLink = 0;
            if (t.get(u).id != -1)
                t.get(u).endLink = u;
            else
                t.get(u).endLink = t.get(t.get(u).suffixLink).endLink;
            return;
        }
        int v = t.get(t.get(u).p).suffixLink;
        char c = t.get(u).c;
        while (true) {
            if (t.get(v).child[c - 'a'] != -1) {
                t.get(u).suffixLink = t.get(v).child[c - 'a'];
                break;
            }
            if (v == 0) {
                t.get(u).suffixLink = 0;
                break;
            }
            v = t.get(v).suffixLink;
        }
        if (t.get(u).id != -1)
            t.get(u).endLink = u;
        else
            t.get(u).endLink = t.get(t.get(u).suffixLink).endLink;
    }
    void build() {
        Queue<Integer> Q = new LinkedList<>();
        Q.add(0);
        while (!Q.isEmpty()) {
            int u = Q.poll();
            link(u);
            for (int v = 0; v < 26; v++) {
                if (t.get(u).child[v] != -1) {
                    Q.add(t.get(u).child[v]);
                }
            }
        }
    }
    int match(String text) {
        int u = 0;
        int ans = 0;
        for (int j = 0; j < text.length(); j++) {
            int i = text.charAt(j) - 'a';
            while (true) {
                if (t.get(u).child[i] != -1) {
                    u = t.get(u).child[i];
                    break;
                }
                if (u == 0)
                    break;
                u = t.get(u).suffixLink;
            }
            int v = u;
            while (true) {
                v = t.get(v).endLink;
                if (v == 0) break;
                ans++;
/*
====================================================================
* Found word #" + t.get(v).id + " at position " + idx
* 
* palabra encontrada, crear String words[] y almacenar durante la lectura
* String found = words[t.get(v).id];
* 
=====================================================================
* Si queremos almacenar los indices en los que aparece (inicio, fin)
* se puede usar un ArrayList[] o un HasMap<String, List<pair<Integer, Integer>>>
* int idx = j + 1 - lengths.get(t.get(v).id);
* int inicio = idx - found.length() + 1;
* int fin = idx;
* mp[t.get(v).id].add(new pair<Integer, Integer>(inicio, fin));
=====================================================================
    * 
*/
                v = t.get(v).suffixLink;
            }
        }
        return ans;
    }
}
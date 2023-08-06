 // Aho_corasick implementacion corta

    //para poder imprimir las palabras
    //que van apareciendo -> crear ArrayList<String> p;


    static class Aho_Corasick {

        final int N = 200000;
        int trie[][] = new int[N][256];
        int nodes = 0;
        int fail[] = new int[N];
        int end_word[] = new int[N];

        //almacena los indices en los que aparece una cadena (inicio, fin) 
        LinkedHashMap<String, ArrayList<pair<Integer, Integer>>> mp = new LinkedHashMap<>();

        void add(String s, int idx) {
            int node = 0;
            for (int i = 0; i < s.length(); i++) {
                char ch = s.charAt(i);
                if (trie[node][ch] == 0) {
                    trie[node][ch] = ++nodes;
                }
                node = trie[node][ch];
            }
            end_word[node] = idx;
        }

        void build() {
            Queue<Integer> q = new LinkedList<>();
            for (int ch = 0; ch < 256; ch++) {
                if (trie[0][ch] > 0) {
                    q.add(trie[0][ch]);
                }
            }
            while (!q.isEmpty()) {
                int u = q.poll();
                for (int ch = 0; ch < 256; ch++) {
                    int v = trie[u][ch];
                    if (v != 0) {
                        fail[v] = fail[u];
                        while (fail[v] > 0 && trie[fail[v]][ch] == 0) {
                            fail[v] = fail[fail[v]];
                        }
                        fail[v] = trie[fail[v]][ch];
                        q.add(trie[u][ch]);
                    }
                }
            }
        }

        int count(String text) {
            int node = 0;
            int ans = 0;
            for (int i = 0; i < text.length(); i++) {
                char ch = text.charAt(i);
                while (node > 0 && trie[node][ch] == 0) {
                    node = fail[node];
                }
                node = trie[node][ch];
                int tmp_node = node;
                while (tmp_node > 0) {
                    if (end_word[tmp_node] > 0) {
                        ans++;
                        //String que aparece en text
                        String s = p.get(end_word[tmp_node] - 1);
                        //(inicio, fin)
                        int start = i - s.length() + 1;
                        int end = i;
                        mp.get(s).add(new pair<>(start, end));
                        // sa.print(p.get(word[tmp_node]-1)+"\n");
                    }
                    tmp_node = fail[tmp_node];
                }
            }
            return ans;
        }

    }
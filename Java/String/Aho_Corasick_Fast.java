

//Aho_corasick mas rapido

static class Aho_Corasick {
        final int N = 200000;
        int trie[][] = new int[N][256];
        int nodes = 0;
        int fail[] = new int[N];
        int word[] = new int[N];

        void add(String s, int idx) {
            int node = 0;
            for (int i = 0; i < s.length(); i++) {
                char ch = s.charAt(i);
                if (trie[node][ch] == 0) {
                    trie[node][ch] = ++nodes;
                }
                node = trie[node][ch];
            }
            word[node] = idx;
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
                    if (word[tmp_node] > 0) {
                        ans++;
                        // sa.println(p.get(word[tmp_node]));
                    }
                    tmp_node = fail[tmp_node];
                }
            }
            return ans;
        }

    }
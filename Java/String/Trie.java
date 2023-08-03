




static class Node {
        int cont;
        Node child[];

        public Node() {
            this.cont = 0;
            child = new Node[26];
        }
    }

    static class Trie {
        Node root;

        Trie() {
            root = new Node();
        }

        void insert(String s) {
            Node curr = root;
            for (int i = 0; i < s.length(); ++i) {
                char c = s.charAt(i);
                if (curr.child[c - 'a'] == null) {
                    curr.child[c - 'a'] = new Node();
                }
                curr.child[c - 'a'].cont++;
                curr = curr.child[c - 'a'];
            }
        }


        /* 
        
            if (x.first == 0 && x.second == 0 || len < s.length()) {
                sa.write("NO ESTÁ\n");
            } else {
                sa.write("SI ESTÁ\n");
            }

         */
        pair<Integer, Integer> query(String s) {
            Node curr = root;
            for (int i = 0; i < s.length(); ++i) {
                char c = s.charAt(i);
                if (curr.child[c - 'a'] == null) {
                    return new pair<Integer, Integer>(i, curr.cont);
                }
                curr = curr.child[c - 'a'];
            }
            return new pair<Integer, Integer>(s.length(), curr.cont);
        }
    }




    static class Node {
        Node childs[];

        Node() {
            childs = new Node[2];
        }
    }

    static class Trie {
        Node root;
        HashSet<Integer> nums;

        Trie() {
            root = new Node();
            nums = new HashSet<>();
        }

        void insert(int x) {
            if (!nums.contains(x)) {
                Node cur = root;
                int i = 32;
                while (i-- > 0) {
                    int bit = (x >> i) & 1;
                    if (cur.childs[bit] == null) {
                        cur.childs[bit] = new Node();
                    }
                    cur = cur.childs[bit];
                }
                nums.add(x);
            }
        }

        //max xor entre un elemento y query
        int maxXorQuery(int query) {
            Node cur = root;
            int ans = 0;
            int i = 32;
            while (i-- > 0) {
                int bit = (query >> i) & 1;
                if (cur.childs[1 - bit] != null) {
                    ans = ans | (1 << i);
                    cur = cur.childs[1 - bit];
                } else {
                    cur = cur.childs[bit];
                }
            }
            return ans;
        }

        //maximo xor entre dos elementos en un arreglo
        int maxXor(int[] arr) {
            int n = arr.length;
            int max_val = 0;
            insert(arr[0]);
            for (int i = 1; i < n; i++) {
                max_val = max(maxXorQuery(arr[i]),max_val);
                insert(arr[i]);
            }
            return max_val;
        }

    }

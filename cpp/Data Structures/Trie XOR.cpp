struct Node {
    Node* childs[2];
};

struct Trie {
    Node* root;

    Trie(){
        root = new Node();
    }

    void insert(int x){
        Node* cur = root;
        int i = 32;
        while (i--) {
            int bit = (x >> i) & 1;
            if (cur->childs[bit] == NULL) {
                cur->childs[bit] = new Node();
            }
            cur = cur->childs[bit];
        }
    }

    // max xor entre un elemento y query
    int maxXorQuery(int query){
        Node* cur = root;
        int ans = 0;
        int i = 32;
        while (i--) {
            int bit = (query >> i) & 1;
            if (cur->childs[1 - bit] != NULL) {
                ans = ans | (1 << i);
                cur = cur->childs[1 - bit];
            } else {
                cur = cur->childs[bit];
            }
        }
        return ans;
    }

    // maximo xor entre dos elementos en un arreglo
    int maxXor(vi &arr){
        int n = sz(arr);
        int max_val = 0;
        insert(arr[0]);
        for (int i = 1; i < n; i++) {
            max_val = max(maxXorQuery(arr[i]), max_val);
            insert(arr[i]);
        }
        return max_val;
    }
};

struct Node {
  int cnt;
  Node* child[26];
};

struct Trie {
  Node* root;
  Trie() {
    root = new Node();
  }

  void insert(const string &s) {
    Node* cur = root;
    int len = 0;
    forn(i, sz(s)) {
      ++len;
      char c = s[i] - 'a';
      if (cur->child[c] == NULL) {
        cur->child[c] = new Node();
      }
      cur->child[c]->cnt++;
      cur = cur->child[c];
    }
  }

  pair<int, int> query(const string &s) {
    Node* cur = root;
    forn (i, sz(s)) {
      char c = s[i] - 'a';
      if (cur->child[c] == NULL) {
        return {i, cur->cnt};
      }
      cur = cur->child[c];
    }
    return {sz(s), cur->cnt};
  }
};
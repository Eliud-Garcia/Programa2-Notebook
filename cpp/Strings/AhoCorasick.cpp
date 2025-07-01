
//https://github.com/JJuanJr/Notebook-ICPC/blob/main/String/AhoCorasick.cpp
Complejidad:
build(|patrones| * M)
Complejidad:
query(|text|)


const int M = 26;
struct node {
    vector<int> child;
    int p = -1;
    char c = 0;
    int suffixLink = -1, endLink = -1;
    int id = -1;
    //int cnt = 0; Para contar patrones repetidos
    node(int p = -1, char c = 0) : p(p), c(c) {
        child.resize(M, -1);
    }
};

struct AhoCorasick {
    vector<node> t;
    vector<int> lenghts;
    int wordCount = 0;

    AhoCorasick() {
        t.emplace_back();
    }

    void add(const string & s) {
        int u = 0;
        for(char c : s) {
            if(t[u].child[c-'a'] == -1) {
                t[u].child[c-'a'] = t.size();
                t.emplace_back(u, c);
            }
            u = t[u].child[c-'a'];
        }
        t[u].id = wordCount++;
        lenghts.push_back(s.size());
    }

    void link(int u) {
        if(u == 0) {
            t[u].suffixLink = 0;
            t[u].endLink = 0;
            return;
        }
        if(t[u].p == 0) {
            t[u].suffixLink = 0;
            if(t[u].id != -1) t[u].endLink = u;
            else t[u].endLink = t[t[u].suffixLink].endLink;
            return;
        }
        int v = t[t[u].p].suffixLink;
        char c = t[u].c;
        while(true) {
            if(t[v].child[c-'a'] != -1) {
                t[u].suffixLink = t[v].child[c-'a'];
                break;
            }
            if(v == 0) {
                t[u].suffixLink = 0;
                break;
            }
            v = t[v].suffixLink;
        }
        if(t[u].id != -1) t[u].endLink = u;
        else t[u].endLink = t[t[u].suffixLink].endLink;
    }

    void build() {
        queue<int> Q;
        Q.push(0);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            link(u);
            for(int v = 0; v < M; ++v)
                if(t[u].child[v] != -1)
                    Q.push(t[u].child[v]);
        }
    }

    int match(const string & text) {
        int u = 0;
        int ans = 0;
        for(int j = 0; j < text.size(); ++j) {
            int i = text[j] - 'a';
            while(true) {
                if(t[u].child[i] != -1) {
                    u = t[u].child[i];
                    break;
                }
                if(u == 0) break;
                u = t[u].suffixLink;
            }
            int v = u;
            while(true) {
                v = t[v].endLink;
                if(v == 0) break;
                ++ans;
                int idx = j + 1 - lenghts[t[v].id];
                // cout << "Found word #" << t[v].id << " at position " << idx << "\n";
                v = t[v].suffixLink;
            }
        }
        return ans;
    }
};

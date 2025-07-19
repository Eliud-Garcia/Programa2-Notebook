

// [1, n]
template<typename T>
struct STree {
    vector<T> tree;
    int n;
    T neutro = T(0);

    T oper(T a, T b) {
        return a + b;
    }

    STree(vector<T> &a) {
        int tam = 1;
        while(1LL << (tam) < sz(a)) tam++;
        n = 1LL << tam;
        tree.resize(n * 2);
        forab(i, 1, sz(a) + 1) upd(i, a[i - 1]);
    }

    void upd(int i, T x) {
        i += n;
        tree[i] = x;
        while (i > 1) {
            i /= 2;
            // The index of the left child is s * 2.
            // The index of the right child is s * 2 + 1.
            tree[i] = oper(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    T qry(int l, int r) {
        T res = 0;
        l += n;
        r += n;
        while (l <= r) {
            if (l % 2 == 1) res = oper(res, tree[l++]);
            if (r % 2 == 0) res = oper(res, tree[r--]);
            l /= 2;
            r /= 2;
        }
        return res;
    }

    //lower bound in the prefix sum
    int lb(T k) {
        int s = 1;
        while (s < n) {
            if (tree[s * 2] >= k) {
                s = s * 2;
            } else {
                k -= tree[s * 2];
                s = s * 2 + 1;
            }
        }

        return s - n;
    }
};




struct node {
    int start, end, maxLen;
    /*{start, end}*/
};

struct SegTreeRegularBracket {
    vector<node> seg;
    int size;

    SegTreeRegularBracket(string& ch)
    {
        size = ch.length();
        seg.resize(4 * size);
        build(1, 1, size - 1, ch);
    }

    void build(int idx, int s, int e, string& ch)
    {
        if (s == e) {
            if (ch[s] == '(') {
                seg[idx] = { 1, 0 };
            } else {
                seg[idx] = { 0, 1 };
            }
            return;
        }
        build(idx << 1, s, (s + e) / 2, ch);
        build(idx << 1 | 1, (s + e) / 2 + 1, e, ch);
        seg[idx] = { seg[idx << 1 | 1].start, seg[idx << 1].end };
        int dif = seg[idx << 1].start - seg[idx << 1 | 1].end;
        int mini = min(seg[idx << 1].start, seg[idx << 1 | 1].end);
        seg[idx].maxLen += mini * 2 + seg[idx << 1 | 1].maxLen + seg[idx << 1].maxLen;
        if (dif > 0) {
            seg[idx].start += dif;
        } else {
            seg[idx].end -= dif;
        }
    }

    node query(int idx, int s, int e, int l, int r)
    {
        if (l > e || s > r) {
            return { 0, 0 };
        }
        if (s >= l && e <= r) {
            return seg[idx];
        }
        node p1 = query(idx << 1, s, (s + e) / 2, l, r);
        node p2 = query(idx << 1 | 1, (s + e) / 2 + 1, e, l, r);
        node ans = { p2.start, p1.end };
        int dif = p1.start - p2.end;
        ans.maxLen += p1.maxLen + p2.maxLen;
        ans.maxLen += min(p1.start, p2.end) * 2;
        if (dif > 0) {
            ans.start += dif;
        } else {
            ans.end -= dif;
        }
        return ans;
    }
    // [1, n]
    node query(int l, int r)
    {
        return query(1, 1, size - 1, l, r);
    }
};
// https://codeforces.com/contest/380/problem/C

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string w;
    cin >> w;
    w = "0" + w; // se agrega un comodin al inicio
    SegTreeRegularBracket seg(w);
    int q, l, r;
    cin >> q;
    while (q--) {
        cin >> l >> r;
        cout << (seg.query(l, r).maxLen) << ln;
    }

    return 0;
}
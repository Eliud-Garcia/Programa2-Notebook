
    static class node {
        public int start, end, maxLen, c;

        public node(int x, int y) {
            this.start = x;
            this.end = y;
        }

        public String toString() {
            return start + " " + end;
        }
    }

    static class SegTreeRegularBracket {
        node seg[];
        int size;

        public SegTreeRegularBracket(String ch) {
            size = ch.length();
            seg = new node[4 * size];
            build(1, 1, size - 1, ch);
        }

        void build(int idx, int s, int e, String ch) {
            if (s == e) {
                if (ch.charAt(s) == '(') {
                    seg[idx] = new node(1, 0);
                } else {
                    seg[idx] = new node(0, 1);
                }
                return;
            }
            build(idx << 1, s, (s + e) / 2, ch);
            build(idx << 1 | 1, (s + e) / 2 + 1, e, ch);
            seg[idx] = new node(seg[idx << 1 | 1].start, seg[idx << 1].end);
            int dif = seg[idx << 1].start - seg[idx << 1 | 1].end;
            int mini = min(seg[idx << 1].start, seg[idx << 1 | 1].end);
            seg[idx].maxLen += mini * 2 + seg[idx << 1 | 1].maxLen + seg[idx << 1].maxLen;
            if (dif > 0) {
                seg[idx].start += dif;
            } else {
                seg[idx].end -= dif;
            }
        }

        node query(int idx, int s, int e, int l, int r) {
            if (l > e || s > r) {
                return new node(0, 0);
            }
            if (s >= l && e <= r) {
                return seg[idx];
            }
            node p1 = query(idx << 1, s, (s + e) / 2, l, r);
            node p2 = query(idx << 1 | 1, (s + e) / 2 + 1, e, l, r);
            node ans = new node(p2.start, p1.end);
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

        node query(int l, int r) {
            return query(1, 1, size - 1, l, r);
        }
    }
    // https://codeforces.com/contest/380/problem/C

    public static void main(String[] args) throws IOException {
        String w = next();
        // agregamos un comodin al inicio de la cadena
        SegTreeRegularBracket seg = new SegTreeRegularBracket("0" + w);
        int q = nextInt();
        while (q-- > 0) {
            int l = nextInt();
            int r = nextInt();
            sa.println(seg.query(l, r).maxLen);
        }
        sa.close();
    }

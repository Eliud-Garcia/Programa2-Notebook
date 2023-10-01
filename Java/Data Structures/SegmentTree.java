

    //indexado desde 0
    static class SegmentTree<T> {
        int n;
        ArrayList<T> st;
        T neutro;
        BinaryOperator<T> oper;

        SegmentTree(ArrayList<T> a, BinaryOperator<T> op, T neutro) {
            n = a.size();
            st = new ArrayList<>(Collections.nCopies(n * 4, null));
            this.neutro = neutro;
            oper = op;

            build(1, 0, n - 1, a);
        }

        void build(int v, int tl, int tr, ArrayList<T> a) {
            if (tl == tr) {
                st.set(v, a.get(tl));
                return;
            }
            int tm = (tr + tl) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm + 1, tr, a);
            st.set(v, oper.apply(st.get(v * 2), st.get(v * 2 + 1)));
        }

        T query(int v, int tl, int tr, int l, int r) {
            if (tl > r || tr < l)
                return neutro;
            if (l <= tl && tr <= r)
                return st.get(v);
            int tm = (tl + tr) / 2;
            return oper.apply(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
        }

        void upd(int v, int tl, int tr, int pos, T val) {
            if (tl == tr) {
                st.set(v, val);
                return;
            }
            int tm = (tr + tl) / 2;
            if (pos <= tm)
                upd(v * 2, tl, tm, pos, val);
            else
                upd(v * 2 + 1, tm + 1, tr, pos, val);
            st.set(v, oper.apply(st.get(v * 2), st.get(v * 2 + 1)));
        }

        void upd(int pos, T val) {
            upd(1, 0, n - 1, pos, val);
        }
        // l inclusive  r exclusive
        // indexado desde cero
        T query(int l, int r) {
            return query(1, 0, n - 1, l, r);
        }
    }


     //Example
     
     /* 
     ArrayList<Long> arr = new ArrayList<>();
     BinaryOperator<Long> oper = (a, b) -> min(a, b);
     SegmentTree<Long> st = new SegmentTree<Long>(arr, oper, 0L);
     Long QUERY = st.query(l, r);
     println(QUERY == null ? 0 : QUERY); -> validar query que no sea null


     int l, r;
     if( 1 <= query <= n){
        l--;
        r--;
        st.query(l ,r);
    }
    
    if( 0 <= query <= n){
        r--;
        st.query(l ,r);
     }

     */

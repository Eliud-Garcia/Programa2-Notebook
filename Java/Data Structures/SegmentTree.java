public class Template {

    public static void main(String[] args) {
        BinaryOperator<Long> oper = (a, b) -> Math.min(a, b); //define la operacion del segmentTree
        Long neutro = Long.valueOf(1000000007); // Neutro 
        SegmentTree<Long> st = new SegmentTree<Long>(arr, oper, neutro); // Recibe una List<>, BinaryOperator<> y el neutro
        
        //ejemplo de uso
        m= 1;
        while (m-- > 0) {
            int o = en.nextInt(), l = en.nextInt(), r = en.nextInt();
            if (o == 1) {
                Long aux = (long) r;
                st.upd(l, aux);
            } else {
                r--;
                Long qu = st.query(l, r);
                sa.println(qu == null ? 0 : qu); // importante validar que no sea null
            }
        }
    }

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

        T query(int l, int r) {
            return query(1, 0, n - 1, l, r);
        }
    }

}
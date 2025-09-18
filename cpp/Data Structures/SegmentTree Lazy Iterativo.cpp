

const int LOG = 17; //calcular
const int MAXN = 2e5;

//[0, n - 1]
template<typename T>
struct STree {
    T seg[2 * MAXN], lazy[2 * MAXN];

    int n;

    T oper(T a, T b) {
        return a + b;
    }

    // suma x en la posición p de tamaño tam
    void poe(int p, T x, int tam, bool prop=1) {
        seg[p] += x * tam;
        if (prop and p < n) lazy[p] += x;
        //######
    }

    // actualiza todos los padres de la hoja p
    void sobe(int p) {
        for (int tam = 2; p /= 2; tam *= 2) {
            seg[p] = oper(seg[2 * p], seg[2 * p + 1]);
            poe(p, lazy[p], tam, 0);
        }
    }

    // propaga la ruta desde la raíz hasta la hoja p
    void prop(int p) {
        int tam = 1 << (LOG - 1);
        for (int s = LOG; s; s--, tam /= 2) {
            int i = p >> s;
            if (lazy[i]) {
                poe(2 * i, lazy[i], tam);
                poe(2 * i + 1, lazy[i], tam);
                lazy[i] = 0;//####
            }
        }
    }

    void build(int n2, vector<T> &v) {
        n = n2;
        for (int i = 0; i < n; i++) seg[ n + i] = v[i];
        for (int i = n - 1; i; i--) seg[i] = oper(seg[2 * i], seg[2 * i + 1]);
        for (int i = 0; i < 2 * n; i++) lazy[i] = 0; //##########
    }

    T query(int a, int b) {
        T ret = 0; //#######
        for (prop(a += n), prop(b += n); a <= b; ++a /= 2, --b /= 2) {
            if (a % 2 == 1) ret = oper(ret, seg[a]);
            if (b % 2 == 0) ret = oper(ret, seg[b]);
        }
        return ret;
    }

    void upd(int a, int b, T x) {
        int a2 = a += n, b2 = b += n, tam = 1;
        for (; a <= b; ++a /= 2, --b /= 2, tam *= 2) {
            if (a % 2 == 1) poe(a, x, tam);
            if (b % 2 == 0) poe(b, x, tam);
        }
        sobe(a2), sobe(b2);
    }
};


/*

    STree<int> st;
    vector<int> a = {1, 2, 3, 1, 1, 1, 1, 1};
    st.build(sz(a), a);
*/


//minimum range queries with updates

const int oo = 1e9 + 50;
const int MAXN = 2e5 + 5;

const int S = sqrt(MAXN);//block size
const int B = MAXN / S + 1; //# de bloques

int a[MAXN];
int blocks[B];

int get_idx(int i){
    //es el indice donde inicia el
    //bloque en el que cae i
    return (i / S) * S;
}

int main() {
    int n, q;
    cin >> n >> q;
    forn(i, n) cin >> a[i];

    fill(blocks, blocks + B, oo);

    forn(i, n){
        blocks[i / S] = min(blocks[i / S], a[i]);
    }

    while(q--){
        int o;
        cin >> o;
        if(o == 1){
            //modify
            int id, v;
            cin >> id >> v;
            id--;
            a[id] = v;
            blocks[id / S] = oo;

            int l = get_idx(id);
            int r = min(n, l + S);

            forab(i, l, r){
                blocks[i / S] = min(blocks[i / S], a[i]);
            }

        }else{
            int l, r;
            cin >> l >> r;
            l--, r--;
            int mn = oo;
            int i = l;
            while(i <= r){
                if(i % S == 0 && i + S < r){
                    mn = min(mn, blocks[i / S]);
                    i += S;
                }else{
                    mn = min(mn, a[i]);
                    i++;
                }
            }
            cout << mn << ln;
        }
    }
    return 0;
}
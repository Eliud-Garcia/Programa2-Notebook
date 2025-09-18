//Segtree lazy code here

const int MAXN = 2e5  + 10;
vi g[MAXN];

int val[MAXN]; // value of each node
vll st_val(MAXN); // STree array
STree<ll> st(MAXN); // segtree

struct HLD {
	vi in, tam, par, hp;
	int timer;

	HLD(int root, int n){
        timer = 0;
        in.resize(n); //tin
        tam.resize(n); //subtree size
        par.resize(n); //parent
        hp.resize(n); //heavy path

        build_hld(root);
        st.build(1, 0, sz(st_val) - 1, st_val);
	}

    //save all values first in st_val and then build segtree
    //or keep updating the segment tree

	void build_hld(int u, int p = -1, int f = 1) {
		st_val[in[u] = timer++] = val[u];
        //st.upd(in[k], in[k], val[k]);
		tam[u] = 1;
		//dont forget the &
		//with edges use [v, w] and check pair(first, second)
		for (auto &v : g[u]) if (v != p) {
			par[v] = u;
			hp[v] = (v == g[u][0] ? hp[u] : v);
			build_hld(v, u, f);
			tam[u] += tam[v];

			if (tam[v] > tam[g[u][0]] || g[u][0] == p) swap(v, g[u][0]);
		}
		if (p * f == -1) build_hld(hp[u] = u, -1, timer = 0);
	}

	ll query_path(int a, int b) {
        //if (a == b) return 0;
		if (in[a] < in[b]) swap(a, b);

		if (hp[a] == hp[b]){
            return st.query(in[b], in[a]); // in[b] + 1 if the value is on the edge
		}
		return st.query(in[hp[a]], in[a]) + query_path(par[hp[a]], b);
	}

	void update_path(int a, int b, int x) {
        //if(a == b) return;
		if (in[a] < in[b]) swap(a, b);

		if (hp[a] == hp[b]){
            return (void) st.upd(in[b], in[a], x); // in[b] + 1 if the value is on the edge
		}

		st.upd(in[hp[a]], in[a], x);
		update_path(par[hp[a]], b, x);
	}

	ll query_subtree(int a) {
		return st.query(in[a], in[a] + tam[a] - 1);
	}

	void update_subtree(int a, int x) {
		st.upd(in[a], in[a] + tam[a] - 1, x);
	}

	int lca(int a, int b) {
		if (in[a] < in[b]) swap(a, b);
		return hp[a] == hp[b] ? b : lca(par[hp[a]], b);
	}
};

/*
If the value is on the edge,
the node that stores the value is the one at the greater depth,
and in queries and updates the higher one is excluded.
*/

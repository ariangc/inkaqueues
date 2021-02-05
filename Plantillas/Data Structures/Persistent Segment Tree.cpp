// Persistent Segment Tree - Gracias Phibrain
// Update en punto x, query en intervalo [l,r)
// Cada llamada de update retorna un nuevo root

// usage:
//	Llenar el vector st.arr (con push back) y correr build()
//	update(root,pos,x): Update +x en pos de version en root
//	query(root,l,r): Query de Op en intervalo [l,r)
//	clear(): Limpia todo

struct PersistentST{
	int n;
	int OpId = 0;
	vector<int> arr;
	vector<int> L, R;
	vector<int> tree;

	int Op(int a, int b){ return a + b;}

	int new_node(int l, int r){
		L.pb(l); R.pb(r); tree.pb(Op(tree[l], tree[r]));
		return sz(tree) - 1;
	}

	int new_node(int x){
		L.pb(0); R.pb(0); tree.pb(x);
		return sz(tree) - 1;
	}

	int build(int a, int b){
		if(a + 1 == b) return new_node(arr[a]);
		int lch = build(a, (a + b) / 2);
		int rch = build((a + b) / 2, b);
		return new_node(lch, rch);
	}

	int update(int tid, int a, int b, int pos, int x){
		if(a + 1 == b) return new_node(Op(tree[tid], x));
		int mid = (a + b) / 2;
		if(pos < mid){
			int new_left = update(L[tid], a, mid, pos, x);
			return new_node(new_left, R[tid]);
		}
		else{
			int new_right = update(R[tid], mid, b, pos, x);
			return new_node(L[tid], new_right);
		}
	}

	int query(int tid, int a, int b, int l, int r){
		if(b <= l || a >= r) return OpId;
		if(a >= l && b <= r) return tree[tid];
		int lch = query(L[tid], a, (a + b) >> 1, l, r);
		int rch = query(R[tid], (a + b) >> 1, b, l, r);
		return Op(lch, rch);
	}
	
	void clear(){
		tree.clear(); L.clear(); R.clear(); arr.clear();
	}
	
	inline int build(){ n = sz(arr); return build(0, n);}
	inline int update(int root, int pos, int x){ return update(root, 0, n, pos, x);}
	inline int query(int root, int l, int r){ return query(root, 0, n, l, r); }
}st;


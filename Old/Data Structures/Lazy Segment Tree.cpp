struct ST{
	ll n, lazy[1<<19], ar[1<<19];
	ii tree[1<<19];

	inline ii Op(ii &val1, ii &val2) { return val1.ff>val2.ff? val1: val2;}
	inline void updpro(ll laz, ll id, ll l, ll r) {
		if(laz) {
			tree[id].ff+=laz;
			lazy[id]+=laz;
		}
	}
	inline void proh(ll id, ll l, ll r){
		ll mid=(l+r)>>1;
		updpro(lazy[id], id<<1, l, mid);
		updpro(lazy[id], id<<1|1, mid, r);
		lazy[id]=0;
	}
	inline void Upd(ll x, ll y, ll val, ll id, ll l, ll r) {
		if(x>=r or y<=l) return ;
		if(x<=l and r<=y) {
			updpro(val, id, l, r);
			return;
		}
		proh(id, l, r) ;
		ll mid=(l+r)>>1;
		Upd(x, y, val, id<<1, l, mid);
		Upd(x, y, val, id<<1|1, mid, r);
		tree[id]=Op(tree[id<<1], tree[id<<1|1]);
	}
	inline ii Que(ll x, ll y, ll id, ll l, ll r) {
		if(x>=r or y<=l) return ii{-INF, -1};
		if(x<=l and r<=y) return tree[id];
		proh(id, l, r);
		ll mid=(l+r)>>1;
		ii left, right;
		left=Que(x, y, id<<1, l, mid);
		right=Que(x, y, id<<1|1, mid, r);
		return Op(left, right);
	}
	inline void Build(ll id, ll l, ll r) {
		if(l+1==r) {
			tree[id]=ii{ar[l], l};
			return ;
		}
		ll mid=(l+r)>>1;
		Build(id<<1, l, mid), Build(id<<1|1, mid, r) ;
		tree[id]=Op(tree[id<<1], tree[id<<1|1]);
	}
	inline void build() { fill(lazy, 0), Build(1, 0, n);}
	inline void upd(ll x, ll y, ll val) { Upd(x, y, val, 1, 0, n);}
	inline ii que(ll x, ll y) { return Que(x, y, 1, 0, n);}
}st; 
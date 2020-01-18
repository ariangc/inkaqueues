//Sack Guni DS
//Solves Lomsat Gelral:
//Sum of all dominating colors in the subtree of vertex v
//Color c is dominating in the subtree of vertex v
//if there are no other colors that appear in the subtree
//of vertex v more times than color c 

ll tsz[1<<17], d[1<<17], big[1<<17], col[1<<17];
ll sum[1<<17], cnt[1<<17], fre[1<<17], val, ans[1<<17];
vi adj[1<<17];

struct ST{
	ll n, t[1<<19];
	inline ll Op(ll &val1, ll &val2){
		return val1+val2;
	}
	inline void Upd(ll p, ll val, ll id, ll l, ll r){
		if(l>p || r<=p) return;
		if(l+1==r && l==p){
			t[id]+=val;
			return;
		}
		ll mid=(l+r)>>1;
		Upd(p, val, id<<1, l, mid);
		Upd(p, val, id<<1|1, mid, r);
		t[id]=Op(t[id<<1], t[id<<1|1]);
	}

	inline ll find(ll id, ll l, ll r){
		if(l+1==r && t[id]!=0) return t[id];
		ll valor=t[id<<1|1], mid=(l+r)>>1;
		if(!valor) return find(id<<1, l, mid);
		return find(id<<1|1, mid, r);
 	}

 	inline void build() { fill(t, 0);}
 	inline void upd(ll p, ll val) { Upd(p, val, 1, 0, n);}
 	inline ll que() { return find(1, 0, n);}
}st;

inline void add(ll v, ll p, ll x){
	ll valor=fre[col[v]];
	st.upd(valor, -col[v]);
	fre[col[v]]+=x;
	valor=fre[col[v]];
	st.upd(valor, col[v]);
	for(auto xd: adj[v]) if(xd!=p && !big[xd]) add(xd,v,x);
}


inline void dfs(ll u, ll pp, ll depth){
	d[u]=depth, tsz[u]=1;
	for(auto xd: adj[u]) if(xd!=pp) dfs(xd, u, depth+1), tsz[u]+=tsz[xd];
}

inline void go(ll u, ll p, ll x){
	ll w=-1, bc=-1;
	for(auto xd: adj[u]) if(xd!=p && tsz[xd]>w) w=tsz[xd], bc=xd;
	for(auto xd: adj[u]) if(xd!=bc && xd!=p) go(xd, u, 0);
	if(bc!=-1) go(bc, u, 1), big[bc]=1;
	add(u, p, 1);
	ans[u]=st.que();
	if(bc!=-1) big[bc]=0;
	if(x==0) add(u, p, -1);
}


int main(){
	fastio;
	ll n; cin>>n;
	st.n=n;
	FER(i, 1, n+1) cin>>col[i];
	FER(i, 0, n-1){
		ll a, b; cin>>a>>b; //a--, b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	st.build();
	dfs(1, -1, 0);
	go(1, -1, 1);
	FER(i, 1, n+1) cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}

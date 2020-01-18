// Paralel Binary Search
// Key idea is to mantain a node with the range and depth
// then use a queue mantaining a ni current nivel and nt current index
// in a grid, given heights of a the mountain, find the smallest height that
// are in a path from 2 given coordenates.
// i.e. Mountainers cf gym 102021 M

ll val[1<<19];
ll nn, mm;
 
struct node{
	ll l, r, d;
	vi v;
	node(){}
	node(ll l, ll r, ll d): l(l), r(r), d(d){}
	inline void clear(){
		l=r=d=0;
		v.clear();
	}
};
struct Kruskal{
	ll n, id[1<<19];
	vector<tri> v;
	inline void build(){
		FER(i,0,n) id[i]=i;
	} 
	inline ll find(ll x){
		while(id[x]!=x) id[x]=id[id[x]], x=id[x];
		return x;
	}
	inline void unir(ll a, ll b){
		ll p=find(a), q=find(b);
		id[p]=id[q];
	}
	inline ll go(ll lim, ll idx){
		FER(i,idx,sz(v)){
			ll w=v[i].tm1, a=v[i].tm2, b=v[i].tm3;
			if(w>=lim){
				return i;
			}
			ll node=a*mm+b;
			FER(t1, -1, 2) FER(t2, -1, 2){
				if(abs(t1)+abs(t2)!=1) continue;
				ll x=a+t1, y=b+t2;
				if(x>=0 && x<nn && y>=0 && y<mm){
					ll cur=x*mm+y;
					if(val[cur]<lim){
						unir(cur, node);
					}
				}
			}
		}
		return sz(v);
	}
}kr;
 
ii queries[1<<19];
ll ans[1<<19];

int main(){
	fastio;
	ll n, m, k; cin>>n>>m>>k;
	nn=n, mm=m;
	kr.n=n*m+1;
	FER(i,0,n){
		FER(j,0,m) {
			ll w; cin>>w;
			ll node=i*m+j;
			val[node]=w;
			kr.v.pb({w, {i, j}});
		}
	}
	kr.build();
	sort(all(kr.v));
	ll ini=0;
	FER(i,0,k){
		ll x1, y1; cin>>x1>>y1; x1--, y1--;
		ll node1=x1*m+y1;
		ll x2, y2; cin>>x2>>y2; x2--, y2--;
		ll node2=x2*m+y2;
		if(node1==node2){
			ans[i]=val[node1];
			continue;
		}
		queries[i]={node1, node2};
	}
	node cur, cur1, cur2;
	cur.l=0, cur.r=1e9, cur.d=0;
	FER(i,0,k) if(!ans[i]) cur.v.pb(i);
	queue<node> q;
	q.push(cur); cur.clear();
	ll ni=-1, nt=0;
	while(sz(q)){
		cur=q.front(); q.pop();
		if(cur.d!=ni) {
			kr.build();
			ni=cur.d, nt=0;
		}
		ll mid=(cur.l+cur.r)>>1;
		nt=kr.go(mid, nt);
		if(cur.l+1==cur.r){
			nt=kr.go(cur.r, nt);
			for(auto xd: cur.v){
				ll a=queries[xd].ff, b=queries[xd].ss;
				ll p1=kr.find(a), p2=kr.find(b);
				(p1==p2)? ans[xd]=mid: ans[xd]=-1;
			}
			continue;
		}
		for(auto xd: cur.v){
			ll a=queries[xd].ff, b=queries[xd].ss;
			ll p1=kr.find(a), p2=kr.find(b);
			(p1==p2)? cur1.v.pb(xd): cur2.v.pb(xd);
		}
		cur1.l=cur.l, cur1.r=mid, cur1.d=cur.d+1;
	    cur2.l=mid, cur2.r=cur.r, cur2.d=cur.d+1;
	    if(sz(cur1.v)) q.push(cur1);
	    if(sz(cur2.v)) q.push(cur2);
	    nt=kr.go(cur.r, nt);
	    cur.clear(), cur1.clear(), cur2.clear();
	}
	FER(i,0,k){
		assert(ans[i]>=0);
		cout<<ans[i]<<endl;
	}
	return 0;
}
// Find pisano of Fib[i]%x
// i.e. Spoj pisano

inline ll bm(ll a, ll b, ll m){
	if(a==0) return 0LL;
	if(a&1) {
		ll x=bm(a-1, b, m);
		x+=b;
		if(x>=m) x-=m;
		return x;
	}
	ll x=bm(a>>1, b, m);
	x<<=1;
	if(x>=m) x-=m;
	return x;
}
 
 
struct matrix{
	ll ar[2][2];
	inline void clear(){
		fill(ar, 0);
	}
};
 
matrix ind;
 
inline matrix mul(matrix &a, matrix b, ll m){
	matrix ty;
	FER(i,0,2) FER(j,0,2){
		ll ans=0;
		FER(k,0,2){
			ans+=bm(a.ar[i][k], b.ar[k][j], m);
			if(ans>=m) ans-=m;
		}
		ty.ar[i][j]=ans;
	}
	return ty;
}
 
 
inline matrix bpmatrix(matrix &a, ll n, ll m){
	if(n==1) return a;
	if(n&1) return mul(a, bpmatrix(a, n-1, m), m);
	matrix x=bpmatrix(a, n>>1, m);
	return mul(x, x, m);
}
 
 
inline ll fib(ll n, ll m){
	matrix cur=bpmatrix(ind, n, m);
	return cur.ar[0][1];
}

// here we need the pollard rho algorithm
// asuming that we have that here


map<ll, ll> mapis;
 
inline bool testpisano(ll n, ll m){
	if(fib(1+n, m)==1 && fib(2+n, m)==1) return true;
	return false;
}
 
inline ll pisanoprime(ll n, ll m){
	ll resp=n, ans, cur;
	vii v;
	make(resp);
	construct(v);
	for(auto xd: v){
		ans=1LL, cur=-1;
		FER(i, 0, xd.ss+1){
			if(testpisano(resp/ans, m)) cur=ans;
			ans*=xd.ff;
		}
		resp/=cur;
	}
	return resp;
}
 
 
inline ll pisano(ll n){
	if(mapis.count(n)) return mapis[n];
	ll p=n%5, m=n-1;
	if(p==1 || p==4) return mapis[n]=pisanoprime(m, n); 
	m+=2, m<<=1;
	return mapis[n]=pisanoprime(m, n);
}
 
inline ll binpow(ll a, ll n){
	if(!n) return 1LL;
	if(n&1) return a*binpow(a, n-1);
	ll x=binpow(a, n>>1);
	return sqr(x);
}
 
inline ll findpisano(ll n){
	vii v;
	make(n);
	construct(v);
	ll ans, cur, resp=1LL;
	for(auto xd: v){
		ans=binpow(xd.ff, xd.ss-1);
		cur=pisano(xd.ff)*ans;
		ans=__gcd(resp, cur);
		resp/=ans;
		resp*=cur;
	}
	return resp;
}
 
 
 
int main(){
	fastio;
	build();
	// because of pollard rho template
	ind.ar[0][0]=1, ind.ar[0][1]=1;
	ind.ar[1][0]=1, ind.ar[1][1]=0;
	mapis[2]=3, mapis[3]=8, mapis[5]=20;
	ll t; cin>>t;
	while(t--){
		ll x; cin>>x;
		cout<<findpisano(x)<<endl;
	}
	return 0;
} 


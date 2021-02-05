// ................   Stirling Numbers Second Kind    ....................

// Building second kind of stirling numbers
// based on stir(n, k)=k*stir(n-1, k)+stir(n-1, k-1)
// stir(i, 0)=stir(0, i)=0, stir(0, 0)=1
// pow(x, p)= sum[k={1,...,p}]{stir(p, k)*k!*comb(x, k)
// sum[x={1, ..., n}]{pow(x, p}= 
// sum[k={1,...,p}]{stir(p, k)*k!*comb(n+1, k+1)


ll stir[1<<10][1<<10], dp[1<<10], dpi[1<<10];

inline ll bp(ll a, ll n, ll m){
	if(!n) return 1LL%m;
	if(n&1) return (a*bp(a, n-1, m))%m;
	ll x=bp(a, n>>1, m);
	return (x*x)%m;
}
inline void Build(ll n, ll k, ll m){
	FER(i,0,n) stir[i][0]=0;
	FER(i,0,n) stir[0][i]=0;
	stir[0][0]=1;
	FER(i,1,n+1){
		FER(j,1,k+1){
			stir[i][j]=(j*stir[i-1][j]+stir[i-1][j-1])%m;
		}
	}
	dp[0]=dp[1]=1;
	dpi[1]=1;
	FER(i,2,n) {
		dp[i]=(dp[i-1]*i)%m;
		dpi[i]=(dpi[i-1]*bp(i, m-2, m))%m;
	}
}

inline ll FindSum(ll n, ll k, ll m){
	ll ans=0, cur=1, coe=(n), comb=n+1;
	if(!k) return n;
	FER(i,1,k+1){
		cur=(dp[i]*stir[k][i])%m;
		comb=(comb*coe)%m;
		cur=(comb*cur)%m;
		cur=(cur*dpi[i+1])%m;
		ans+=cur;
		if(ans>=m) ans-=m;
		coe--;
	}
	return ans;
}

int main(){
	Build(350, 350, mod);
	ll t, n, k, froz, ands, tnt; scanf("%lld", &t);
	while(t--){
		scanf("%lld%lld", &n, &k);
		froz=FindSum(n, k, mod);
		ands=FindSum(n, k+1, mod);
		tnt=(froz*(n+1)-ands+mod)%mod;
		if(tnt>=mod) tnt-=mod;
		if(tnt<0) tnt+=mod;
		printf("%lld\n", tnt);
	}
	return 0;
}

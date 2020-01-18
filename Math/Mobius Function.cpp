// Mobius function

vi mo, lp, primes;
ll ar[1<<20], cnt[1<<20];

inline void ContructMobius(ll n){
   lp.resize(n+1, -1), mo.resize(n+1, -1);
   mo[1]=1;
   FER(i, 2, n+1){
      if(lp[i]==-1) lp[i]=i, primes.pb(i);
      ll j=0;
      for(; j<sz(primes) && primes[j]*i<=n && primes[j]< lp[i]; j++){
         lp[primes[j]*i]=primes[j], mo[primes[j]*i]=-mo[i];
      }
      if(primes[j]*i<=n) mo[primes[j]*i]=0;
   }
}

int main(){
   fastio;
   ContructMobius(1e6);
   ll n; cin>>n;
   FER(i,0,n) cin>>ar[i], cnt[ar[i]]++;
   ll ans=0;
   FER(i, 1, 1e6+1){
      for(ll j=i<<1; j<=1e6; j+=i) cnt[i]+=cnt[j];
   }
   FER(i, 1, 1e6+1) ans+=mo[i]*(sqr(cnt[i])-cnt[i])*(cnt[i]-2)/6;
   cout<<ans<<endl;
   return 0;
}
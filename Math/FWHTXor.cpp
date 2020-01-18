// FWHT XOR

inline ll bp(ll a, ll n){
   if(n==0) return 1;
   if(n&1) return (a*bp(a, n-1))%mod;
   ll x=bp(a, n>>1);
   return (sqr(x)%mod+mod)%mod;
}

// Fast Walsh-Hadamard Transform for xor multiplication
// take note about the matrix associated
// |+1 +1|
// |+1 -1|
// The inverse is the same as the matrix, so it's not necesary
// to have a bool parameter in the convolution

struct FWHTXor{
   ll n;
   inline void GetInverse(vi &v){
      n=1;
      while(n<sz(v)) n<<=1;
      v.resize(n);
      for(ll len=1; (len<<1)<=n; len<<=1){
         for(ll i=0; i<n; i+=(len<<1)){
            FER(j,0,len){
               ll a=v[i+j], b=v[i+j+len];
               v[i+j]=(a+b)%mod;
               v[i+j+len]=(mod+a-b)%mod;
            }
         }
      }
   }
}fwht;
int main(){
   fastio;
   ll n, k; cin>>n>>k;
   vi v;
   FER(i,0,k+1) v.pb(1);
   fwht.GetInverse(v);
   FER(i,0,fwht.n) v[i]=bp(v[i], n);
   fwht.GetInverse(v);
   ll inv=bp(fwht.n, mod-2), ans=0;
   FER(i,1,fwht.n){
      ans+=(v[i]*inv)%mod;
      ans%=mod;
   }
   cout<<ans<<endl;
   return 0;
}

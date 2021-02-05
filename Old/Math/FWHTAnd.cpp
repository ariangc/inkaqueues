// FWHT And

inline ll bp(ll a, ll n){
   if(n==0) return 1;
   if(n&1) return (a*bp(a, n-1))%mod;
   ll x=bp(a, n>>1);
   return (sqr(x)%mod+mod)%mod;
}

// Fast Walsh-Hadamard Transform  for And multiplication
// take note about the matrix associated
// |-1 +1|
// |+1 +0|
// The inverse is not the same as the matrix, so it's necesary
// to have a bool parameter in the convolution

struct FWHTAnd{
   ll n;
   inline void GetInverse(vi &v, ll flag){
      n=1;
      while(n<sz(v)) n<<=1;
      v.resize(n);
      for(ll len=1; (len<<1)<=n; len<<=1){
         for(ll i=0; i<n; i+=(len<<1)){
            FER(j,0,len){
               ll a=v[i+j], b=v[i+j+len];
               if(flag){
                  v[i+j]=b;
                  v[i+j+len]=a+b;
                  v[i+len+j]%=mod;
               }
               else{
                  v[i+j]=mod-a+b;
                  v[i+j+len]=a;
                  v[i+j]%=mod;
               }
            }
         }
      }

   }
}fwht;
int main(){
   fastio;
   ll n, top=0, ans=0; cin>>n;
   vi v1, v2;
   FER(i,0,n){
      ll x; cin>>x;
      top=max(top, x);
      v1.pb(x);
   }
   top++;
   v2.resize(top);
   v2[0]=1;
   for(auto xd: v1) v2[xd]=1;
   fwht.GetInverse(v2, 1);
   FER(i,0,fwht.n) v2[i]=bp(v2[i], n);
   fwht.GetInverse(v2, 0);
   FER(i,0,fwht.n) if(v2[i]) ans++;
   cout<<ans<<endl;
   return 0;
}

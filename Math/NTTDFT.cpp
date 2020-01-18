//NTT

struct NTT{
   ll root_1, root, root_pw;
   inline ll bp(ll a, ll b){
      if(b==0) return 1;
      if(b&1) return (a*(bp(a, b-1)))%mod;
      ll x=bp(a, b>>1)%mod;
      x=(x+mod)%mod;
      return ((x*x)%mod+mod)%mod;;
   }
   inline ll inverse(ll a){
      return bp(a, mod-2);
   }
   inline void build(){
      // Si:c*pow(2, k)+1=mod
      // Entonces root cumple:
      // pow(root, 1<<(pow(2, k))=1mod
      // Mejor complejidad=Primary root test.
      root_pw=1<<23;
      FER(i,2,1e5+1) if(bp(i, root_pw)==1){ root=i; break;}
      root_1=inverse(root);
   }
   inline void fft(vi &a , bool inv){
      ll n=sz(a);
      for(ll i=1, j=0; i<n; i++){
         ll bt=n>>1;
         for(; j&bt; bt>>=1) j^=bt;
         j^=bt;
         if(i<j) swap(a[i], a[j]);
      }
      for(ll len=2; len<=n; len<<=1){
         ll wlen=inv? root_1: root;
         for(ll i=len; i<root_pw; i<<=1) wlen=(sqr(wlen)%mod+mod)%mod;
         for(ll i=0; i<n; i+=len){
            ll w=1;
            for(ll j=0; j<len/2; j++){
               ll u=a[i+j], v=(a[i+j+len/2]*w)%mod;
               a[i+j]=u+v<mod? u+v: u+v-mod;
               a[i+j+len/2]=u-v>=0? u-v: u-v+mod;
               w=((w*wlen)%mod+mod)%mod;
            }
         }
      }
      if(inv){
         ll n_1=inverse(sz(a));
         for(auto &xd: a) xd=((xd*n_1)%mod+mod)%mod;
      }
   }
   inline vi GetConvolution(vi a, vi b){
      ll n=1;
      while(n<sz(a)+sz(b)) n<<=1;
      a.resize(n), b.resize(n);
      fft(a, false), fft(b, false);
      FER(i,0,n) a[i]=((a[i]*b[i])%mod+mod)%mod;
      fft(a, true);
      return a;
   }
   inline vi BinPolyExp(vi &a, ll b){
      if(b==1) return a;
      ll n=1;
      while(n<sz(a)*b) n<<=1;
      a.resize(n);
      fft(a, false);
      for(auto &xd: a) xd=bp(xd, b);
      fft(a, true);
      return a;
   }
}ntt;


int main(){
   fastio;
   NTT ntt;
   ntt.build();
   ll n, k; cin>>n>>k;
   vi v(10);
   FER(i,0,k){
      ll x; cin>>x;
      v[x]=1;
   }
   ll ans=0;
   vi froz=ntt.BinPolyExp(v, n/2);
   for(auto xd: froz) ans=(ans+sqr(xd))%mod;
   ans=(ans+mod)%mod;
   cout<<ans<<endl;
   return 0;
}

/* Pi Function*/

ll vis[10000005], cant[10000005], phi[100005][105];
vi primos;

inline ll FindPhi(ll x, ll p){
   if(!p) return x;
   if(primos[p-1]>=x) return 1;
   if(x<=1e5 && p<=1e2) return phi[x][p];
   return FindPhi(x, p-1)-FindPhi(x/primos[p-1], p-1);
}

inline ll PiFuncion(ll n){
   if(n<1e7) return cant[n];
   ll raizC2=sqrt(n), raizC3=pow(n, 1.0/3.0);
   ll m=PiFuncion(raizC3);
   ll ans=FindPhi(n, m)+m-1;
   for(ll i=m; primos[i]<=raizC2; i++){
      ans-=PiFuncion(n/primos[i]);
      ans+=PiFuncion(primos[i]);
      ans--;
   }
   return ans;
}
int main(){
   fastio;
   FER(i,2,1e7){
      cant[i]+=cant[i-1];
      if(vis[i]) continue;
      cant[i]++;
      primos.pb(i);
      for(ll j=i*i; j<1e7; j+=i) vis[j]++;
   }
   FER(i,0,101){
      FER(j,0,1e5+1) phi[j][i]=i? phi[j][i-1]-phi[j/primos[i-1]][i-1]: j;
   }
   ll n, ans=0; cin>>n;
   for(auto xd: primos){
      ll x=xd, y=n/xd;
      if(sqr(x)>n) break;
      ans+=PiFuncion(y)-PiFuncion(x);
   }
   for(auto xd: primos) {
      if(sqr(xd)*xd<=n) ans++;
      else break;
   }
   cout<<ans<<endl;
   return 0;
}

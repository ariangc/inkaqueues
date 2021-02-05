/* Dynamic Hash
*/

ll len1[N], len2[N];

struct Hash{
   vi dp1, dp2;
   string s;
   ll ans1, ans2, n;
   inline void build(ll id){
      if(!id) ans1=0, ans2=0;
      n=sz(s);
      FER(i, id, n) dp1.pb(0), dp2.pb(0);
      FER(i,id,sz(s)){
         if(s[i]>='a' && s[i]<='z'){
            ans1=(ans1*bas)%mod1;
            ans1+=(s[i]-'a'+1);
            ans2=(ans2*bas)%mod2;
            ans2+=(s[i]-'a'+1);
            if(ans1>=mod1) ans1-=mod1;
            if(ans2>=mod2) ans2-=mod2;
            dp1[i]=ans1, dp2[i]=ans2;
         }
         else if(s[i]>='A' && s[i]<='Z'){
            ans1=(ans1*bas)%mod1;
            ans1+=(s[i]-'A'+27);
            ans2=(ans2*bas)%mod2;
            ans2+=(s[i]-'A'+27);
            if(ans1>=mod1) ans1-=mod1;
            if(ans2>=mod2) ans2-=mod2;
            dp1[i]=ans1, dp2[i]=ans2;
         }
         else{
            ans1=(ans1*bas)%mod1;
            ans1+=(s[i]-'0'+55);
            ans2=(ans2*bas)%mod2;
            ans2+=(s[i]-'0'+5);
            if(ans1>=mod1) ans1-=mod1;
            if(ans2>=mod2) ans2-=mod2;
            dp1[i]=ans1, dp2[i]=ans2;
         }
      }
   }
   inline ii Query(ll l, ll r){
      ll ans1=dp1[r-1], ans2=dp2[r-1];
      if(l){
         ll add1=(dp1[l-1]*len1[r-l])%mod1;
         ll add2=(dp2[l-1]*len2[r-l])%mod2;
         ans1-=add1, ans2-=add2;
         if(ans1<0) ans1+=mod1;
         if(ans2<0) ans2+=mod2;
         return {ans1, ans2};
      }
      return {ans1, ans2};
   }
};

int main(){
   fastio;
   ll t1=1, t2=1;
   FER(i,0,N) {
      len1[i]=t1;
      len2[i]=t2;
      t1=(t1*bas)%mod1;
      t2=(t2*bas)%mod2;
   }
   return 0;
}

/* Persistent Trie */
struct Ptrie{
   ll nod, m[1<<23][2], ind[1<<24];
   inline ll AddTrie(ll last, ll i, ll val, ll pos){
      ll rt=nod++;
      if(i<0) return rt;
      ll r=(val>>i)&1;
      m[rt][r^1]=m[last][r^1];
      m[rt][r]=AddTrie(m[last][r], i-1, val, pos);
      ind[m[rt][r]]=pos;
      return rt;
   }

   inline ll QueryMax(ll id, ll val, ll pos){
      ll ans=0;
      IFR(i,19,0){
         ll r=(val>>i)&1;
         if(m[id][r^1]) {
            ll curnod=m[id][r^1];
            ll index=ind[curnod];
            if(index>=pos) id=m[id][r^1], ans+=((r^1)<<i);
            else id=m[id][r], ans+=(r<<i);
         }
         else {
            id=m[id][r], ans+=(r<<i);
         }
      }
      return ans ^ val;
   }
}st;

int main(){
   st.nod=1
   st.AddTrie(), st.QueryMax();
}

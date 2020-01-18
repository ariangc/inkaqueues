struct T{
   ll nxt[1<<6], fail, cnt;
   inline void clear(){
      fill(nxt, 0);
      fail=cnt=0;
   }
};
 
inline ll Find(char &s){
   if(s>='a' and s<='z') return s-'a';
   if(s>='A' and s<='Z') return s-'A'+26;
   if(s>='0' and s<='9') return s-'0'+52;
   return 62;
}

struct AhoCorasick{
   vector<T> t;
   T nil;
   ll id, nod;
   vi End, Q, ans, cnt;
   vector<string> set;
   inline void init(){
      nod=0;
      t.clear();
      End.clear();
      Q.clear();
      ans.clear();
      cnt.clear();
      nil.clear();
      set.clear();
      t.pb(nil);
      End.pb(-1);
      Q.pb(-1);
      cnt.pb(0);
   }
   
   inline void Add(string &st){
      ll cur=0, idx;
      for(auto xd: st){
         idx=Find(xd);
         if(!t[cur].nxt[idx]) t[cur].nxt[idx]=++nod, t.pb(nil), cnt.pb(0);
         cur=t[cur].nxt[idx];
      } 
      End.pb(cur);
      cnt[cur]++;
      set.pb(st);
   } 
   inline void Build(){
      id=1;
      FER(i,0,1<<6) if(t[0].nxt[i])  Q.pb(t[0].nxt[i]);
      while(id<=sz(Q)-1){
         ll u=Q[id++];
         cnt[u]+=cnt[t[u].fail];
         FER(i,0,1<<6){
            ll v=t[u].nxt[i];
            if(!v){
               t[u].nxt[i]=t[t[u].fail].nxt[i];
               continue;
            }
            Q.pb(v);
            t[v].fail=t[t[u].fail].nxt[i];     
         }
      }
   }
 
   inline void AddText(string &st){
      ll cur=0, idx;
      for(auto xd: st){
         idx=Find(xd);
         cur=t[cur].nxt[idx];
         t[cur].cnt++;
      }
   }
 
   inline void PushAll(){
      ans.resize(sz(End));
      IFR(i, sz(Q)-1, 1) t[t[Q[i]].fail].cnt+=t[Q[i]].cnt;
      FER(i, 1, sz(ans)) ans[i]=t[End[i]].cnt;
   }
 
   inline ll Get(string &st){
      ll cur=0, idx, ans=0, n;
      for(auto xd: st){
         idx=Find(xd);
         cur=t[cur].nxt[idx];
         ans+=cnt[cur];
      }
      return ans;
   }
}ac[20][2];


inline void Upd(ll n, ll idx, string &s){
   ll id=-1;
   FER(i, 0, 20){
      ll val=(n>>i)&1;
      if(!(val)) {id=i; break;}
   }
   ac[id][idx].init();
   FER(i, 0, id){
      for(auto xd: ac[i][idx].set) ac[id][idx].Add(xd);
      ac[i][idx].init();
   }
   ac[id][idx].Add(s);
   ac[id][idx].Build();
} 


inline void Query(string &s){
   ll ans=0;
   FER(i, 0, 20){
      if(sz(ac[i][0].set)) ans+=ac[i][0].Get(s);
      if(sz(ac[i][1].set)) ans-=ac[i][1].Get(s);
   }
   cout<<ans<<endl;
   cout.flush();
}
int main(){
   fastio;
   ll q, t, tot1=0, tot2=0; cin>>q;
   string s;
   while(q--){
      cin>>t>>s;
      if(t==1){
         Upd(tot1, 0, s);
         tot1++;
      }
      else if(t==2){
         Upd(tot2, 1, s);
         tot2++;
      }
      else{
         Query(s);
      }
   }   
   return 0;
}
/* Dynamic Segment Tree Beats */

struct T{
   ll fmx, fmn, smx, smn;
   T(){}
   T(ll fmx, ll fmn, ll smx, ll smn):
      fmx(fmx), fmn(fmn), smx(smx), smn(smn){}

   inline T Op(T a, T b){
      if(a.fmx < b.fmx){
         a.smx=a.fmx;
         a.fmx=b.fmx;
      }
      if(a.fmx == b.fmx){
         a.smx=max(a.smx, b.smx);
      }
      else a.smx=max(a.smx, b.fmx);
      if(a.fmn > b.fmn){
         a.smn=a.fmn;
         a.fmn=b.fmn;
      }
      if(a.fmn==b.fmn){
         a.smn=min(a.smn, b.smn);
      }
      else a.smn=min(a.smn, b.fmn);
      return a;
   }
   inline void Umax(ll x){
      if(fmx==fmn) fmx=x;
      if(smx==fmn) smx=x;
      fmn=x;
   }
   inline void Umin(ll x){
      if(fmn==fmx) fmn=x;
      if(smn==fmx) smn=x;
      fmx=x;
   }
};
 
struct Dinamic_Segment_Tree_Beats{
   ll n, nodes, root;
   T lazy[N];
   ll L[N], R[N];

   inline void updpro(T val, ll id, ll l, ll r){
      if(val.fmx<lazy[id].fmx){
         lazy[id].Umin(val.fmx);
      }
      if(val.fmn>lazy[id].fmn){
         lazy[id].Umax(val.fmn);
      }
   }

   inline void newLeaf(T val, ll id, ll l, ll r){
      lazy[id]=val;
   }

   inline void proh(ll id, ll l, ll r){
      ll mid=(l+r)>>1;
      if(l+1==r) return ;
      if(!L[id]){
         L[id]=nodes++;
         newLeaf(lazy[id], L[id], l, mid);
      }
      else updpro(lazy[id], L[id], l, mid);
      if(!R[id]){
         R[id]=nodes++;
         newLeaf(lazy[id], R[id], mid, r);
      }
      else updpro(lazy[id], R[id], mid, r);
   }

   inline void UpdMax(ll x, ll y, ll val, ll &id, ll l, ll r){
      if(!id){
         id=nodes;
         L[id]=R[id]=0;
         nodes++;
      }
      proh(id, l, r);
      if(x>=r || y<=l || lazy[id].fmn>=val) return;
      if(x<=l && r<=y && lazy[id].smn>val && lazy[id].fmn<val) {
         lazy[id].Umax(val);
         return;
      }
      ll mid=(l+r)>>1;
      if(x<mid) UpdMax(x, y, val, L[id], l, mid);
      if(y>mid) UpdMax(x, y, val, R[id], mid, r);
      lazy[id]=lazy[id].Op(lazy[L[id]], lazy[R[id]]);
   }

   inline ll Sol(ll x, ll y, ll id, ll l, ll r){
      proh(id, l, r);
      if(x>=r || y<=l) return -INF;
      if(x<=l && r<=y) return lazy[id].fmx;
      ll mid=(l+r)>>1, left, right;
      left=Sol(x, y, L[id], l, mid);
      right=Sol(x, y, R[id], mid, r);
      return max(left, right);

   }

   inline void build() {
      nodes=1, root=0; 
      FER(i, 1, 2){
         lazy[i].fmx=lazy[i].smx=-INF;
         lazy[i].fmn=lazy[i].smn=INF;
         lazy[i].fmx=lazy[i].fmn=-1;
      }
   }

   inline void updMax(ll x, ll y, ll val) { UpdMax(x, y, val, root, 1, n);}
   inline ll que(ll x, ll y) { return Sol(x, y, root, 1, n);}
}st;

int main(){
   fastio;
   ll n, q; cin>>n>>q;
   st.n=n+1;
   st.build();
   st.updMax(1, st.n, 0);
   ll l, r, x, t;
   FER(i, 0, q){
      cin>>t;
      if(t==1){
         cin>>l>>r>>x;
         st.updMax(l, r+1, x);
      }
      else {
         cin>>l>>r;
         x=st.que(l, r+1);
         cout<<x<<endl;
      }
   }
   return 0;
}

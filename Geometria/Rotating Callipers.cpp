/* Maximum Distance of a pair of points 
in a Range Using Rotatin Calipers and Segment Tree
Note that to build the convex hull in a range 
always there at least 2 points less for that 
we can build the convexhull, for queries
we just construct what we need */

struct PT{
   ll x, y;
   PT(){}
   PT(ll x, ll y): x(x), y(y){}
};
 
PT points[1<<18];
ll tt[1<<18];


ll GetDist(PT &a, PT &b){
   return sqr(a.x-b.x)+sqr(a.y-b.y);
}

inline ll GetOri(ll id1, ll id2, ll id3){
   ll r=(points[id2].y-points[id1].y)*
      (points[id3].x-points[id1].x);
   r-=(points[id2].x-points[id1].x)*
      (points[id3].y-points[id1].y);
   return (r==0)? 0: ((r>0)? 1: -1);
}

inline bool compare(ll id1, ll id2){
   if(points[id1].x<points[id2].x) return true;
   if(points[id1].x==points[id2].x and 
   points[id1].y<points[id2].y) return true;
   return false;
}



struct ConvexHull{
   vi uh, lh;
   ll count=0;
   inline void set(ll i){
      uh.resize(1, i);
      lh.resize(1, i);
      count=1;
   }
};
// Dinamic Segment Tree

struct ST{
   vector<ConvexHull> t;
   ll n;
   
   inline ll Join(vi &v1, vi &v2, ll *tt){
      ll i=0, j=0, k=0, n1=sz(v1), n2=sz(v2);
      while(i<n1 && j<n2){
         if(compare(v1[i], v2[j])) tt[k++]=v1[i++];
         else tt[k++]=v2[j++];
      }
      while(i<n1) tt[k++]=v1[i++];
      while(j<n2) tt[k++]=v2[j++];
      return k;
   }

   inline ConvexHull Op(ConvexHull &t1, ConvexHull &t2){
      if(t1.count==0) return t2;
      if(t2.count==0) return t1;
      ConvexHull ty;
      ll count=Join(t1.uh, t2.uh, tt), l=0, r=0;
      FER(i,0,count){
         while(l>1 and GetOri(tt[l-2], tt[l-1], tt[i])<=0) --l;
         tt[l++]=tt[i];
      }
      ty.uh.insert(ty.uh.end(), tt, tt+l);
      count=Join(t1.lh, t2.lh, tt);
      FER(i,0,count){
         while(r>1 and GetOri(tt[r-2], tt[r-1], tt[i])>=0) --r;
         tt[r++]=tt[i];
      }
      ty.lh.insert(ty.lh.end(), tt, tt+r);
      ty.count=sz(ty.uh)+sz(ty.lh)-2;
      if(ty.count==0) ty.count=1;
      return ty;
   } 

   ST(ll n): n(n), t(2*n){
      FER(i,0,n) t[i+n].set(i);
      IFR(i, n-1, 1) t[i]=Op(t[i<<1], t[i<<1|1]);
   }

   inline ConvexHull Query(ll l, ll r){
      ConvexHull ans;
      for(l+=n, r+=n; l<r; l>>=1, r>>=1){
         if(l&1) ans=Op(ans, t[l++]);
         if(r&1) ans=Op(t[--r], ans);
      }
      return ans;
   }

   inline ll que(ll l, ll r){
      if(r-l<=1) return GetDist(points[l], points[r]);
      ConvexHull cur=Query(l, r+1);
      ll lr=sz(cur.uh), rr=sz(cur.lh), i=0, j=rr-1;
      ll ans=0, curdist, val;
      while(i<lr-1 or j>0){
         PT &left=points[cur.uh[i]];
         PT &right=points[cur.lh[j]];
         curdist=GetDist(left, right);
         // first brute force
         if(curdist>ans) ans=curdist;
         if(i==lr-1) --j;
         else if(j==0) i++;
         else{
            // rotating calipers
            PT& t1=points[cur.uh[i+1]];
            PT& t2=points[cur.lh[j-1]];
            val=(t1.y-left.y)*(right.x-t2.x);
            val-=(t1.x-left.x)*(right.y-t2.y);
            if(val>0) i++;
            else --j;
         }
      }
      return ans;
   }
};


int main(){
   fastio;   
   ll n; cin>>n;
   FER(i,0,n) cin>>points[i].x>>points[i].y;
   ST st(n);
   ll q, l, r, froz; cin>>q;
   FER(i,0,q){
      cin>>l>>r; l--, r--;
      froz=st.que(l, r);
      cout<<froz<<endl;
   }
   return 0;
}
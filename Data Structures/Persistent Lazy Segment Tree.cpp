// Persistent Lazy Segment Tree for a hash value
// All implementation are based on The clasical problem

struct T{
    ll a, b, t, s;
    T(){}
    T(ll a, ll b, ll t, ll s): a(a), b(b), t(t), s(s){}
    inline void clear(){
        a=b=t=s=0;
    }
};
 
struct PLST{
    ll n;
    vi L, R, lazy, ar;
    vector<bool> IsLazy;
    vector<T> tree;
    
    inline T Op(T val1, T val2){
        T ty;
        ty.t=val1.t+val2.t;
        ty.s=val1.s+val2.s;
        ty.a=(val1.a*dp1[val2.t])%mod1;
        ty.a+=val2.a;
        ty.b=(val1.b*dp2[val2.t])%mod2;
        ty.b+=val2.b;
        if(ty.a>=mod1) ty.a-=mod1;
        if(ty.b>=mod2) ty.b-=mod2;
        return ty;
    }
    
    inline ll newLazy(ll id, ll add, ll l, ll r){
        L.pb(L[id]), R.pb(R[id]), lazy.pb(add), IsLazy.pb(true);
      ll p=sz(lazy)-1;        
        if(add==INF){
         tree.pb(tree[id]);
         lazy[p]=lazy[id];
         IsLazy[p]=false;
            return p;
        }
        T cur;
        cur.t=r-l, cur.s=(r-l)*add;
        if(add==0) cur.a=ln1[r-l], cur.b=ln2[r-l];
        if(add==1) cur.a=len1[r-l], cur.b=len2[r-l];
        tree.pb(cur);
        return p;
    }
    
    inline ll newParent(ll l, ll r){
        L.pb(l), R.pb(r), tree.pb(Op(tree[l], tree[r]));
        lazy.pb(INF), IsLazy.pb(false);
        return sz(tree)-1;
    }
    
    inline ll newLeaf(T val){
        L.pb(0), R.pb(0), tree.pb(val);
        lazy.pb(INF), IsLazy.pb(false);
         return sz(tree)-1;
    }
    
    inline void proh(ll id, ll l, ll r){
        if(IsLazy[id]){
            if(l>=r) return;    
            ll mid=(l+r)>>1;
            L[id]=newLazy(L[id], lazy[id], l, mid);
            R[id]=newLazy(R[id], lazy[id], mid, r);
            IsLazy[id]=false;
            lazy[id]=INF;
            return;
        }
    }
 
    inline ll updR(ll x, ll y, ll add, ll id, ll l, ll r){
        if(x>=r || y<=l) return id;
        if(x<=l && r<=y) return newLazy(id, add, l, r);
        proh(id, l, r);
        ll mid=(l+r)>>1;
        ll left=updR(x, y, add, L[id], l, mid), right=updR(x, y, add, R[id], mid, r);
        return newParent(left, right);
    }
 
    inline T Query(ll x, ll y, ll id, ll l, ll r){
        if(x>=r || y<=l) return T(0LL, 0LL, 0LL, 0LL);
        if(x<=l && r<=y) return tree[id];
        proh(id, l, r);
        ll mid=(l+r)>>1;
        T left=Query(x, y, L[id], l, mid);
        T right=Query(x, y, R[id], mid, r);
        return Op(left, right);
    }
 
    inline ll Build(ll l, ll r){
        ll mid=(l+r)>>1;
        if(l+1==r) return newLeaf(T(ar[l], ar[l], 1, 0));
        ll left=Build(l, mid), right=Build(mid, r);
        return newParent(left, right);
    }
    
    inline ll que(ll l, ll r, ll timer) { 
        T cur=Query(l, r, timer, 0, n);
        return cur.s;
    }
 
    inline ll find(ll a, ll p, ll l, ll r){
        proh(a, l, r);
        if(l>p) return -1;
        if(l+1==r) return tree[a].s==tree[a].t? -1: l;
        ll mid=(l+r)>>1;
        ll right=find(R[a], p, mid, r);
        if(right!=-1) return right;
        return find(L[a], p, l, mid);
    }
 
    inline ll upd(ll x, ll y, ll add, ll timer) { return updR(x, y, add, timer, 0, n);}
    inline ll build() { return Build(0, n);}
}st;
 

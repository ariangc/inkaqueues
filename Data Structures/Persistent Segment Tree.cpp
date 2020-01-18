struct PST{
    ll n;
    vi L, R, tree, ar;
    inline ll Op(ll &val1, ll &val2) { return val1+val2;}
    inline ll newParent(ll l, ll r){
        L.pb(l), R.pb(r), tree.pb(Op(tree[l], tree[r]));
        return sz(tree)-1;
    }
  
    inline ll newLeaf(ll val){
        L.pb(0), R.pb(0), tree.pb(val);
        return sz(tree)-1;
    }
 
    inline ll updR(ll p, ll add, ll id, ll l, ll r){
        if(l+1==r) return newLeaf(Op(tree[id], add));
        ll mid=(l+r)>>1;
        if(p<mid) return newParent(updR(p, add, L[id], l, mid), R[id]);
        return newParent(L[id], updR(p, add, R[id], mid, r));
    }
  
    inline ll Query(ll x, ll y, ll id, ll l, ll r){
        if(x>=r or y<=l) return 0LL;
        if(x<=l and r<=y) return tree[id];
        ll mid=(l+r)>>1, left, right;
        left=Query(x, y, L[id], l, mid);
        right=Query(x, y, R[id], mid, r);
        return Op(left, right);
    }
  
    inline ll Build(ll l, ll r){
        ll mid=(l+r)>>1;
        if(r-l<2) return newLeaf(ar[l]);
        ll left=Build(l, mid), right=Build(mid, r);
        return newParent(left, right);
    }
 
    inline ll que(ll l, ll r, ll timer) { return Query(l, r, timer, 0, n);}
    inline ll upd(ll p, ll add, ll timer) { return updR(p, add, timer, 0, n);}
    inline ll build() { n=sz(ar); return Build(0, n);}
}st;
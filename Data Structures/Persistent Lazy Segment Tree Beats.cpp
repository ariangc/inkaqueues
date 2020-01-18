struct T{
    ll fmx, fmn, smx, smn, cmx, cmn;
    ll sum, lval, add;
    T(){}
    T(ll fmx, ll fmn, ll smx, ll smn, ll cmx, ll cmn, ll sum): 
        fmx(fmx), fmn(fmn), smx(smx), smn(smn), cmx(cmx), cmn(cmn), sum(sum){}
    inline void clear(){
        lval=INF, add=0;
    }
    inline T Op(T a, T b){
        if(a.fmx<b.fmx){
            a.cmx=0;
            a.smx=a.fmx;
            a.fmx=b.fmx;
        }
        if(a.fmx==b.fmx){
            a.cmx+=b.cmx;
            a.smx=max(a.smx, b.smx);
        }
        else a.smx=max(a.smx, b.fmx);
        if(a.fmn>b.fmn){
            a.cmn=0;
            a.smn=a.fmn;
            a.fmn=b.fmn;
        }
        if(a.fmn==b.fmn){
            a.cmn+=b.cmn;
            a.smn=min(a.smn, b.smn);
        }
        else a.smn=min(a.smn, b.fmn);
        a.sum+=b.sum;
        a.clear();
        return a;
    }
    inline void UMax(ll x){
        sum+=(x-fmn)*cmn;
        if(fmx==fmn) fmx=x;
        if(smx==fmn) smx=x;
        fmn=x;
        if(lval!=INF && lval<x) lval=x;
    }
    inline void Umin(ll x){
        sum+=(x-fmx)*cmx;
        if(fmn==fmx) fmn=x;
        if(smn==fmx) smn=x;
        fmx=x;
        if(lval!=INF && lval>x) lval=x;
    }
 
 
};

struct PLSTB{
    ll n;
    vi L, R, ar;
    vector<T> lazy;
    vector<bool> IsLazy;
    inline void updpro(T val , ll id, ll l,  ll r){
        if(val.fmx<lazy[id].fmx){
            lazy[id].Umin(val.fmx);
        }
        if(val.fmn>lazy[id].fmn){
            lazy[id].UMax(val.fmn);
        }
    }

    inline void updadd(ll val, ll id, ll l, ll r){
        lazy[id].fmx+=val, lazy[id].fmn+=val;
        if(lazy[id].smx!=-INF) lazy[id].smx+=val;
        if(lazy[id].smn!=INF) lazy[id].smn+=val;
        lazy[id].sum+=val*(r-l);
        if(lazy[id].lval!=INF) lazy[id].lval+=val;
        else lazy[id].add+=val;
    }
 
    inline void updput(ll val ,ll id, ll l, ll r){
        lazy[id].fmx=val, lazy[id].fmn=val;
        lazy[id].smx=-INF, lazy[id].smn=INF;
        lazy[id].cmx=r-l;
        lazy[id].cmn=r-l;
        lazy[id].sum=val*(r-l);
        lazy[id].lval=val;
        lazy[id].add=0LL;
    }

    inline ll newLazyCre(ll id, ll l, ll r){
        L.pb(L[id]), R.pb(R[id]);
        lazy.pb(lazy[id]), IsLazy.pb(true);
        return sz(lazy)-1;
    }
    inline ll newParent(ll l, ll r){
        L.pb(l), R.pb(r), IsLazy.pb(false);
        lazy.pb(lazy[0].Op(lazy[l], lazy[r]));
        return sz(lazy)-1;
    }

    inline ll newLeaf(ll val){
        ll p=sz(lazy);
        lazy.pb(T{val, val, -INF, INF, 1, 1, val});
        IsLazy.pb(false), L.pb(0), R.pb(0);
        lazy[p].clear();
        return p;
    }  

    inline void proh(ll id, ll l, ll r){
        if(IsLazy[id]){
            if(l>=r) return;
            ll mid=(l+r)>>1;
            L[id]=newLazyCre(L[id], l, mid);
            R[id]=newLazyCre(R[id], mid, r);
            if(lazy[id].lval!=INF){
                updput(lazy[id].lval, L[id], l, mid);
                updput(lazy[id].lval, R[id], mid, r);
                lazy[id].lval=INF;
                IsLazy[id]=false;
                return;
            }
            if(lazy[id].add){
                updadd(lazy[id].add, L[id], l, mid);
                updadd(lazy[id].add, R[id], mid, r);
                lazy[id].add=0LL;
            }
            updpro(lazy[id], L[id], l, mid);
            updpro(lazy[id], R[id], mid, r);
            IsLazy[id]=false;
        }
    }

    inline ll UpdMin(ll x, ll y, ll val, ll id, ll l, ll r){
        if(x>=r or y<=l or lazy[id].fmx<=val) return id;
        if(x<=l and r<=y and lazy[id].smx<val and lazy[id].fmx>val){
            ll idx=newLazyCre(id, l, r);
            lazy[idx].Umin(val);
            return idx;
        }
        proh(id, l, r);
        ll mid=(l+r)>>1, left, right;
        left=UpdMin(x, y, val, L[id], l, mid);
        right=UpdMin(x, y, val, R[id], mid, r);
        return newParent(left, right);
    }

    inline ll UpdMax(ll x, ll y, ll val, ll id, ll l, ll r){
        if(x>=r or y<=l or lazy[id].fmn>=val) return id;
        if(x<=l and r<=y and lazy[id].smn > val and lazy[id].fmn < val){
            ll idx=newLazyCre(id, l, r);
            lazy[idx].UMax(val);
            return idx;
        }
        proh(id, l, r);
        ll mid=(l+r)>>1, left, right;
        left=UpdMax(x, y, val, L[id], l, mid);
        right=UpdMax(x, y, val, R[id], mid, r);
        return newParent(left, right);
    }

    inline ll UpdQue(ll x, ll y, ll val, ll id, ll l, ll r){
        if(x>=r or y<=l) return id;
        if(x<=l and r<=y){
            ll idx=newLazyCre(id, l, r);
            updadd(val, idx, l, r);
            return idx;
        }
        proh(id, l, r);
        ll mid=(l+r)>>1, left, right;
        left=UpdQue(x, y, val, L[id], l, mid);
        right=UpdQue(x, y, val, R[id], mid, r);
        return newParent(left, right);
    }

    inline ll UpdPut(ll x, ll y, ll val, ll id, ll l, ll r){
        if(x>=r or y<=l) return id;
        if(x<=l and r<=y) {
            ll idx=newLazyCre(id, l, r);
            updput(val, idx, l, r);
            return idx;
        }
        proh(id, l, r);
        ll mid=(l+r)>>1, left, right;
        left=UpdPut(x, y, val, L[id], l, mid);
        right=UpdPut(x, y, val, R[id], mid, r);
        return newParent(left, right);
    }

    inline ll Query(ll x, ll y, ll id, ll l, ll r){
        if(x>=r or y<=l) return 0LL;
        if(x<=l and r<=y) return lazy[id].sum;
        proh(id, l, r);
        ll mid=(l+r)>>1, left, right;
        left=Query(x, y, L[id], l, mid);
        right=Query(x, y, R[id], mid, r);
        return left+right;
    }

    inline ll Build(ll l, ll r){
        ll mid=(l+r)>>1;
        if(l+1==r) return newLeaf(ar[l]);
        ll left=Build(l, mid), right=Build(mid, r);
        return newParent(left, right);
    }

    inline ll que(ll x, ll y, ll root) { return Query(x, y, root, 0, n);}
    inline ll updmax(ll x, ll y, ll val, ll root) { return UpdMax(x, y, val, root, 0, n);}
    inline ll updmin(ll x, ll y, ll val, ll root) { return UpdMin(x, y, val, root, 0, n);}
    inline ll updA(ll x, ll y, ll val, ll root) { return UpdQue(x, y, val, root, 0, n);}
    inline ll updP(ll x, ll y, ll val, ll root) { return UpdPut(x, y, val, root, 0, n);}
    inline ll build() { n=sz(ar); return Build(0, n);}

}st;


int main(){
    fastio;
    ll n, q; cin>>n>>q;
    FER(i,0,n) {
        ll x; cin>>x;
        st.ar.pb(x);
    }
    ll root=st.build();
    ll l, r, x, t;
    FER(i,0,q){
        cin>>t>>l>>r; l--;
        if(t==1){
            cin>>x;
            root=st.updmin(l, r, x, root);
        }
        else if(t==2){
            cin>>x; 
            root=st.updmax(l, r, x, root);
        }
        else if(t==3){
            cin>>x;
            root=st.updA(l, r, x, root);
        }
        else if(t==4){
            cin>>x;
            root=st.updP(l, r, x, root);
        }
        else{
            x=st.que(l, r, root);
            cout<<x<<endl;
        }
    }
    return 0;
}
// works over a segment tree st

struct HLDES{
    ll n, gid;
    ll tsz[1<<17], rt[1<<17], id[1<<17], idb[1<<17], d[1<<17], p[1<<17], val[1<<17];
    vii adj[1<<17];
    vi v[1<<17];
    inline void dfs(ll u, ll pp, ll depth, ll w){
        tsz[u]=1, d[u]=depth, p[u]=pp, val[u]=w;
        for(auto xd: adj[u]) if(xd.ff!=pp) 
            dfs(xd.ff, u, depth+1, xd.ss), tsz[u]+=tsz[xd.ff];
    }
    inline void go(ll u, ll root){
        rt[u]=root, id[u]=gid++;
        ll w=-1, bc=0;
        for(auto xd: adj[u]) if(xd.ff!=p[u] and tsz[xd.ff]>w) w=tsz[xd.ff], bc=xd.ff;
        if(bc) go(bc, root);
        for(auto xd: adj[u]) if(xd.ff!=p[u] and xd.ff!=bc) go(xd.ff, xd.ff);
    }

    inline void goback(){
        FER(i, 0, n) v[rt[i]].pb(i);
        FER(i, 0, n) if(sz(v[i])) for(auto xd: v[i]){
            idb[xd]=id[i]+sz(v[i])-(d[xd]-d[i])-1;
        } 
    }
    inline void upd(ll a, ll b){
        ll l, r;
        while(rt[a]!=rt[b]){    
            if(d[rt[a]]>d[rt[b]]) swap(a, b);
            l=id[rt[b]], r=id[b]+1;
            st.upd(l, r, 1);
            b=p[rt[b]];
        }
        if(d[a]>d[b]) swap(a, b);
        l=id[a]+1, r=id[b]+1;
        st.upd(l, r, 1);
    }
 
    inline void build(){
        st.n=n, gid=0;
        dfs(0, -1, 0, 0);
        go(0, 0);
        goback();
        FER(i, 0, n) st.ar[id[i]]=val[i];
        st.build();
    }
}hld;

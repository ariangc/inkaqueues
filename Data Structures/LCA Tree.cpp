vi adj[1<<17];
ll p[1<<17][18], be[1<<17], en[1<<17], pos; 
 
inline void dfs(ll u, ll pp){
    p[u][0]=pp, be[u]=pos++;
    FER(i, 1, 18) if(p[u][i-1]!=-1) p[u][i]=p[p[u][i-1]][i-1];
    for(auto xd: adj[u]) if(xd!=pp) dfs(xd, u);
    en[u]=pos++;
}
 
inline bool test(ll a, ll b){
    if(a==-1) return true;
    return be[a]<=be[b] && en[a]>=en[b];
}
 
inline ll lca(ll a, ll b){
    if(test(a, b)) return a;
    if(test(b, a)) return b;
    IFR(i, 17, 0) if(!test(p[a][i], b)) a=p[a][i];
    return p[a][0];
}

inline void build() {fill(p, -1), dfs(0, -1);}

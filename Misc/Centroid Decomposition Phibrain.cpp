//Centroid Decomposition Phibrain

struct CD{
   ll gid, n;
   vi graph[N], adj[N];
   ll tsz[N], p[N], id[N], rt[N];
   ll tsz1[N], p1[N], d1[N];
   inline void add(ll a, ll b){
      graph[a].pb(b);
      graph[b].pb(a);
   }
   inline ll dfs(ll u, ll pp){
      tsz[u]=1;
      for(auto xd: graph[u]) if(xd!=pp && p[xd]==-1) tsz[u]+=dfs(xd, u);
      return tsz[u];
   }
   inline void descompose(ll u, ll pp, ll sb, ll prev){
      for(auto xd: graph[u]) if(xd!=pp && p[xd]==-1 && (tsz[xd]*2) > sb) {descompose(xd, u, sb, prev); return;}
      p[u]=prev; ll pe;
      for(auto xd: graph[u]) if(p[xd]==-1) pe=dfs(xd, -1), descompose(xd, u, tsz[xd], u);
   }
   inline ll dfs1(ll u, ll pp, ll depth){
      p1[u]=pp, d1[u]=depth, tsz1[u]=1;
      for(auto xd: adj[u]) if(xd!=pp) tsz1[u]+=dfs1(xd, u, depth+1);
      return tsz1[u];
   }
   inline void make(ll u){
      ll pe=dfs1(u, -1, 0);
   }
   inline void go(ll u, ll root){
      id[u]=gid++, rt[u]=root;
      ll w=-1, bc=-1;
      for(auto xd: adj[u]) if(xd!=p1[u] && tsz1[xd]>w) w=tsz1[xd], bc=xd;
      if(bc!=-1) go(bc, root);
      for(auto xd: adj[u]) if(xd!=p1[u] && xd!=bc) go(xd, xd);
   }
   inline ll lca(ll a, ll b){
      while(rt[a]!=rt[b]) d1[rt[a]]>d1[rt[b]]? a=p1[rt[a]]: b=p1[rt[b]];
      return d1[a]>d1[b]? b: a;
   } 
   inline void build(ll u){
      FER(i,0,N) p[i]=-1;
      ll ja=dfs(u, -1);
      descompose(u, -1, tsz[u], -2);
      ll nod;
      FER(i,0,n) if(p[i]==-2) {nod=i; break;}
      FER(i,0,n) if(i!=nod) adj[i].pb(p[i]), adj[p[i]].pb(i);
      gid=0;
      make(nod);
      go(nod, nod);
   }
}cd;

//cd.add(a, b); cd.build(0); rooted in 0
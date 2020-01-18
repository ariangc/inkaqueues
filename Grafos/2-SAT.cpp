/* 2-Satisfiability 
   Autor: Phibrain
   Instrucciones de uso:
      assig[i]: 0 pushear, 1: no pushear
      nodes para el nodo n >> true: 2*n, false: 2*n + 1
*/

struct TWOSAT{
   vector<int> adj[N], adjt[N];
   ll n;
   ll comp[N], vis[N], assig[N];
   vector<int> eulerian;
   inline void dfs1(ll u){
      vis[u]=1;
      for(auto xd: adj[u]) if(vis[xd]==0) dfs1(xd);
      eulerian.pb(u);
   }
   inline void dfs2(ll u, ll rt){
      comp[u]=rt;
      for(auto xd: adjt[u]) if(comp[xd]==-1) dfs2(xd, rt);
   }
   inline ll solve(){
      fill(vis, 0), fill(comp, -1), fill(assig, 0);
      ll pos=0;
      FER(i,0,n) for(auto xd: adj[i]) adjt[xd].pb(i);
      FER(i,0,n) if(vis[i]==0) dfs1(i);
      reverse(all(eulerian));
      for(auto xd: eulerian) if(comp[xd]==-1) dfs2(xd, pos++);
      FER(i,0,n/2) assig[i]=1;
      for(ll i=0; i<n; i+=2){
         if(comp[i]==comp[i+1]) return 0;
         assig[i/2]=(comp[i]>comp[i+1]);
      }
      return 1;
   }
};

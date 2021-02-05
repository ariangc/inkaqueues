/* Max flow with upper and lower bounds
   
   add(a, b, c, d): crea un nodo de "a" hacia "b" con lower value de c
   y upper value de "d". Todos los nodos son 1 base

   Implementacion basada en verificar que el frujo es feasible y para encontrar
   el max flow usa binary search

   La construccion del grafo esta dada por construct(sink, source, #de nodos)
   El grafo esta guardado en graph[][] y adj1[]

   Para reconstruir los caminos usar el weighted eulerian path
   
   Usar Push Relabel flow!
*/
#define N1 101
 
ll graph[N1][N1];
vector<tri> adj[N1];
vii adj1[N1];
 
inline void add(ll a, ll b, ll c, ll d){
   adj[a].pb(tri{b, {c, d}});
}
 
inline ll solve(ll x, ll sn, ll sr, ll n, PushRelabel &pr){
   ll nod=0, ands=0, neg=0;
   ll sale[N1], entra[N1], d[N1];
   fill(sale, 0), fill(entra, 0);
   FER(i,0,n+1) adj1[i].clear();
   adj[nod].clear();
   adj[nod].pb(tri{sn, {x, INF}});
   FER(i,0,n+1){
      if(sz(adj[i])) for(auto xd: adj[i]){
         sale[i]+=xd.tm2;
         entra[xd.tm1]+=xd.tm2;
      }
   }
   ll t1=n+1, t2=n+2;
   FER(i, 0, n+1) d[i]=sale[i]-entra[i];
   FER(i, 0, n+1) (d[i]>0)? ands+=d[i] : neg+=-d[i];
   FER(i, 0, n+1) {
      if(d[i]>0) pr.AddEdge(i, t2, d[i]);
      if(d[i]<0) pr.AddEdge(t1, i, -d[i]);
   } 
   FER(i, 0, n+1){
      if(sz(adj[i])) for(auto xd: adj[i]){
         ll w=xd.tm3-xd.tm2;
         pr.AddEdge(i, xd.tm1, w);      
      }
   }
   pr.AddEdge(sr, nod, INF);
   ll froz=pr.GetMaxFlow(t1, t2);
   if(froz==ands && neg==ands) return 1;
   return 0;
}

inline void go(ll x, ll sn, ll sr, ll n){
   PushRelabel pr(n+3);
   ll pe=solve(x, sn, sr, n, pr);
   map<ii, ll> m;
   for(auto xd: pr.G){
      for(auto gg: xd){
         if(gg.flow>0) m[{gg.from, gg.to}]+=gg.flow;
      }
   }
   fill(graph, 0);
   FER(i, 1, n+1){
     if(sz(adj[i]))for(auto xd: adj[i]){
      ll w=xd.tm2+m[{i, xd.tm1}];
      if(w==0) continue;
      graph[i][xd.tm1]=w;
      adj1[i].pb(ii{xd.tm1, w});
     }
   }
}

inline ll construct(ll sn, ll sr, ll n){
   ll ini=0, fin=INF-1;
   FER(i,0,100){
      if(ini+1==fin) break;
      ll mid=(ini+fin)>>1;
      PushRelabel pr(n+3);
      if(solve(mid, sn, sr, n, pr)) ini=mid;
      else fin=mid;
   }
   PushRelabel pr(n+3);
   ll pe=solve(ini, sn, sr, n, pr);
   if(pe && ini) {
      go(ini, sn, sr, n);
      return 1;
   }
   return 0;
}

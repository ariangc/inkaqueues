/* 
   Dado un grafo dirigido con pesos y 2 nodos "a", "b"
   encuentra todos los caminos de "a" hacia "b" 
   
   la idea clave es vacear todos los ciclos recursivamente
   mientras se hace el dfs de "a" hacia "b"
   ... El grafo esta guardado en graph[][] y adj1[]

*/


ll graph[N1][N1];
vii adj1[N1];
 
vi ands, cycles[N1], path[N1], pru[N1], cam[N1];
vector<tri> tnt;
ll vis[N1], mark[N1], visC[N1], enc[N1];
 
inline void GoBack(ll u, ll v, ll &flag, vi &vec){
   if(flag) return;
   enc[u]++;
   vec.pb(u);
   for(auto xd: adj1[u]){
      if(flag) return;
      if(!graph[u][xd.ff]) continue;
      if(xd.ff==v){
         flag++;
         if(flag==1) vec.pb(v);
         return;
      }
      if(!enc[xd.ff]){
         GoBack(xd.ff, v, flag, vec);
         if(!flag) vec.pop_back();
      }   
   }
}
 
 
inline void fillout(ll u){
   vi cur;
   ll ans, flag;
   while(!visC[u]){
      flag=0;
      cur.clear();
      fill(enc, 0);
      GoBack(u, u, flag, cur);
      if(flag){
         ans=INF;
         FER(i, 1, sz(cur)) ans=min(ans, graph[cur[i-1]][cur[i]]);
         FER(i, 1, sz(cur)) graph[cur[i-1]][cur[i]]-=ans;
         FER(j, 0, ans) FER(i, 0, sz(cur)-1) cycles[u].pb(cur[i]);
      }
      else{
         visC[u]++;
         break;
      }
   }
}
 
 
inline void dfs(ll u, ll v){
   if(mark[u]) return;
   mark[u]++;
   if(!visC[u]) fillout(u);
   for(auto xd: cycles[u]) {
      if(!mark[xd]) dfs(xd, v);
      path[v].pb(xd);
   }
}
 
 
inline void findallpaths(ll u, ll v, ll &flag){
   if(flag) return;
   vis[u]++;
   if(!mark[u]){
      dfs(u, u);
      path[u].pb(u);
      for(auto xd: path[u]) ands.pb(xd);
   }
   else ands.pb(u);
   for(auto xd: adj1[u]){
      if(flag) return;
      if(graph[u][xd.ff]==0) continue;
      if(xd.ff==v){
         flag++;
         if(flag==1) ands.pb(v), graph[u][xd.ff]--;
         return;
      }
      if(!vis[xd.ff]){
         graph[u][xd.ff]--;
         findallpaths(xd.ff, v, flag);
      }
   }
}
 
int main(){
   fastio;
   ll cnt=0;
   FER(i, 1, n+1) cnt+=graph[a][i];
   FER(i, 1, n+1) cnt-=graph[i][a];
   cout<<cnt<<endl;
   fill(mark, 0);
   FER(k, 0, cnt){
      FER(i, 1, n+1) vis[i]=0;
      ands.clear();
      t=0;
      findallpaths(a, b, t);
      for(auto xd: ands) cout<<xd<<" "; cout<<endl;
   }
   return 0;
}

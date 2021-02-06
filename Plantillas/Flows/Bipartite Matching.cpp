/* Bipartite matching BFS-DFS
   Autor: elManco
*/

const int INF = 1e9;
int n, m, nil, match[N], dist[N];
vector<int> adj[N];

bool bfs(){
   queue<int> q;
   for(int i = 1; i <= n; ++i){
      if(match[i] == nil){
         dist[i] = 0;
         q.push(i);
      }
      else dist[i] = INF;
   }
   dist[nil] = INF;
   while(!q.empty()){
      int u = q.front();
      q.pop();
      if(u == nil) continue;
      for(int v : adj[u]){
         if(dist[match[v]] == INF){
            dist[match[v]] = dist[u] + 1;
            q.push(match[v]);
         }
      }
   }
   return dist[nil] != INF;
}

bool dfs(int u){
   if(u != nil){
      for(int v : adj[u]){
         if(dist[match[v]] != dist[u] + 1) continue;
         if(dfs(match[v])){
            match[v] = u;
            match[u] = v;
            return true;
         }
      }
      dist[u] = INF;
      return false;
   }
   return true;
}

int bipMatching(){
   nil = n + m + 1;
   for(int i = 1; i <= n+m; ++i)
      match[i] = nil;
   int matching = 0;
   while(bfs()){
      for(int i = 1; i <= n; ++i)
         if(match[i] == nil and dfs(i))
            ++matching;
   }
   return matching;
}

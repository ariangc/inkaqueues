/* Bridges and Articulation Points
   Autor: Froz
   Instrucciones de uso:
      fill(id, -1) antes de usarlo
      En bridge se guardaran los puentes
      art[i] == True si el nodo i es articulacion
*/

const int N = 1e5 + 2;

int low[N], id[N], parent[N];
vector<int> adj[N];
int curr_id =0;
int root, rootchild;

bool art[N];
vector<ii> bridges;

void dfs(int u) {
   low[u] = id[u] = curr_id++;
   for(int &v: adj[u]){
      if (id[v] == -1){
         parent[v] = u;
         if (u == root) rootchild++;
         dfs(v);
         if (low[v] >= id[u]) art[u] = true;
         if (low[v] > id[u]){
            bridges.pb({u, v});
         }
         low[u] = min(low[u], low[v]);
      }
      else if (v != parent[u]) low[u] = min(low[u], id[v]);
   } 
}

//inside int main()
fill(id, -1);
FER(i, 0, n){
   if (id[i] == -1) {
      root = i; rootchild = 0; dfs(i);
      art[root] = (rootchild > 1); 
   } 
}

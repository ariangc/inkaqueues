/* Tarjan's SCC
   Autor: Halim
   Instrucciones de uso:
      Inicializar d[N] en -1!
      No olvidarse de limpiar variables
      Es como un dfs, lanzar un for y correr si nodo actual
      no esta visitado.
*/

vector<int> g[N];
int d[N], low[N], scc[N];
bool stacked[N];
stack<int> s;
int ticks, current_scc;

void tarjan(int u){
  d[u] = low[u] = ticks++;
  s.push(u);
  stacked[u] = true;
  const vector<int> &out = g[u];
  for (int k=0, m=out.size(); k<m; ++k){
   const int &v = out[k];
   if (d[v] == -1){
     tarjan(v);
     low[u] = min(low[u], low[v]);
   }else if (stacked[v]){
     low[u] = min(low[u], low[v]);
   }
  }
  if (d[u] == low[u]){
   int v;
   do{
     v = s.top();
     s.pop();
     stacked[v] = false;
     scc[v] = current_scc;
   }while (u != v);
   current_scc++;
  }
}

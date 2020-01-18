
// Lexicographically smallest toposort

vector<int> g[MAXN];int n;
vector<int> tsort(){
   vector<int> r;priority_queue<int> q;
   vector<int> d(2*n,0);
   FER(i,0,n)FER(j,0,g[i].size())d[g[i][j]]++;
   FER(i,0,n)if(!d[i])q.push(-i);
   while(!q.empty()){
      int x=-q.top();q.pop();r.pb(x);
      FER(i,0,g[x].size()){
         d[g[x][i]]--;
         if(!d[g[x][i]])q.push(-g[x][i]);
      }
   }
   return r;  // if not DAG it will have less than n elements
}

//Floyd - Warshall and Bellman Ford
 
// g[i][j]: weight of edge (i, j) or INF if there's no edge
// g[i][i]=0
ll g[MAXN][MAXN];int n;
void floyd(){ // O(n^3) . Replaces g with min distances
   FER(k,0,n)FER(i,0,n)if(g[i][k]<INF)
      FER(j,0,n)if(g[k][j]<INF)
         g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
bool inNegCycle(int v){return g[v][v]<0;}
bool hasNegCycle(int a, int b){ // true iff there's neg cycle in between
   FER(i,0,n)if(g[a][i]<INF&&
      g[i][b]<INF&&g[i][i]<0)return true;
   return false;
}
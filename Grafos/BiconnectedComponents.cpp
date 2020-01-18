
vector<ii> st;
int tc,n,m,par[N];
int cnt,num[N],low[N];
vector<int> adj[N];
vector< vector<ii> > bcc;

void tarjan(int u, bool root = 0){
   num[u] = low[u] = cnt++;
   int child = 0;
   for(int v : adj[u]) if(v != par[u]){
      if(num[v] == -1){
         child++, par[v] = u;
         st.push_back(ii(u,v));
         tarjan(v);
         low[u] = min(low[u],low[v]);
         if((root && child > 1) || (!root && num[u] <= low[v])){
            vector<ii> tmp;
            while(st.back() != ii(u,v)) tmp.pb(st.back()), st.pop_back();
            tmp.pb(st.back()), st.pop_back();
            bcc.pb(tmp);
         }
      }else if(num[v] < num[u]){
         low[u] = min(low[u],num[v]);
         st.pb(ii(u,v));
      }
   }
}

int main(){

   int TC,a,b;
   cin >> TC;
   for(tc = 1; tc <= TC; ++tc){
      cin >> n >> m;
      bcc.clear();
      for(int i = 0; i <= n; ++i) 
         adj[i].clear();

      for(int i = 0; i < m; ++i){
         cin >> a >> b;
         adj[a].pb(b);
         adj[b].pb(a);
      }
      cnt = 0;
      for(int i = 0; i <= n; ++i)
         par[i] = num[i] = low[i] = -1;

      for(int i = 1; i <= n; ++i) if(num[i] == -1){ 
         tarjan(i,1);
         if(sz(st)) bcc.pb(st);
         st.clear();
      }
   }

   return 0;
}

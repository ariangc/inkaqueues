/* Edmonds Blossom - General matching para grafos generales
   Autor: Phibrain
*/

struct EdmondsBlossom{
   ll n;
   vi match, vis, tmp;
   set<ii> used;
   inline void join(ll a, ll b) {
      match[a]=b, match[b]=a;
   }
   inline bool dfs(ll k, vector<vi> &com, vi &blossom){
      vis[k] = 0;
      FER(i, 0, n) if(com[k][i]){
         if(vis[i] == -1){
            vis[i] = 1;
            if(match[i] == -1 || dfs(match[i], com, blossom)) { join(k, i); return true;}
         }
         if(vis[i] == 0 || sz(blossom)){
            blossom.pb(i), blossom.pb(k);
            if(k == blossom[0]) { match[k] = -1; return true;}
            return false;
         }
      }
      return false;
   }
   inline bool augment(vector<vi> &com){
      FER(m, 0, n) if(match[m] == -1){
         vi blossom;
         vis = vi(n, -1);
         if(!dfs(m, com, blossom)) continue;
         if(sz(blossom) == 0) return true;

         ll base = blossom[0], s = sz(blossom);
         vector<vi> newcom = com;
         
            FER(i, 1, s-1) FER(j, 0, n) newcom[base][j] = newcom[j][base] |= com[blossom[i]][j];
         FER(i, 1, s-1) FER(j, 0, n) newcom[blossom[i]][j] = newcom[j][blossom[i]] = 0;
         newcom[base][base] = 0;
         
            if(!augment(newcom)) return false;
         
            ll k = match[base];
            if(k != -1) FER(i, 0, s) if(com[blossom[i]][k]){
            join(blossom[i], k);
            if(i&1) for(ll j = i + 1; j < s; j += 2) join(blossom[j], blossom[j + 1]);
            else for(ll j = 0; j < i; j += 2) join(blossom[j], blossom[j + 1]);
            break;
         }
         return true;
      }
      return false;
   }
   inline ll edmonds(vector<vi> & com){
      ll res=0;
      match=vi(n, -1);
      while(augment(com)) res++;
      return res;
   }
   inline void preprocess(vector<vi> &com){
      tmp.clear();
      tmp.assign(n, 0);
      FER(i,0,n) com.pb(tmp);
      used.clear();
      match.clear();
      vis.clear();
   }
   inline void add(ll a, ll b, vector<vi> &com){
      if(a>b) swap(a, b);
      if(used.count({a, b})) return;
      used.insert({a, b});
      com[a][b]=com[b][a]=1;
   }
};

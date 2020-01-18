//Iterative Aho - Corasick

#define N 1050
#define MOD 1000003
 
inline char f(char ch){
   if(ch >= 'a' and ch <= 'z') return ch - 'a';
   if(ch >= 'A' and ch <= 'Z') return ch - 'A' + 26;
   return ch - '0' + 52;
} 
 
struct AhoCorasick{
   int cnt;
   char pch[N];
   int t[N][27], gt[N][27],link[N],slink[N],p[N];
   int leaf[N];
 
   AhoCorasick(){
      cnt = 1;
      p[0] = 0;
      fill(t,-1);
      fill(gt,-1);
      fill(link,-1);
      fill(slink,-1);
      fill(leaf,0);
   }
 
   void add_string(string &s, int id){
      int u = 0;
      for(char ch : s){
         int c = f(ch);
         if(t[u][c] == -1){
            t[u][c] = cnt++;
            p[cnt-1] = u;
         }
         u = t[u][c];
         pch[u] = ch;
      }
      leaf[u] = 1;
   }
 
   int get_link(int v){
      if(link[v] == -1){
         if(!v or !p[v]) link[v] = 0;
         else link[v] = go(get_link(p[v]),pch[v]);
      }
      return link[v];
   }
   
   int go(int v, char ch){
      int c = f(ch);
      if(gt[v][c] == -1){
         if(t[v][c] != -1) gt[v][c] = t[v][c];
         else gt[v][c] = (v == 0) ? 0 : go(get_link(v),ch);
      }
      return gt[v][c];
   }
 
   int get_superlink(int u){
      if(slink[u] == -1){
         int lk = get_link(u);
         if(lk == 0) slink[u] = 0;
         else if(leaf[lk]) slink[u] = lk;
         else slink[u] = get_superlink(lk);
      }
      return slink[u];
   }
};
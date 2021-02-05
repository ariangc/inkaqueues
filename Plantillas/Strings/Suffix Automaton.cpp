// Suffix Automaton
// Construccion de Suffix Automaton en O(n).
// len[u]: Máximo tamaño de un string aceptado por u
// link[u]: Suffix link de u
// usage:
//		Para reusar, borrar adj[]
//		sa_extend(c): Extender el automata con el caracter c

const int MAX = 1000000;
int len[MAX*2];
int link[MAX*2];
map<char,int> adj[MAX*2];
int sz, last;

// To reuse, clear adj[]
void sa_init() {
   sz = last = 0;
   len[0] = 0;
   link[0] = -1;
   sz++;
}

void sa_extend (char c) {
   int cur = sz++;
   len[cur] = len[last] + 1;
   int p;
   for (p=last; p!=-1 && !adj[p].count(c); p = link[p])
      adj[p][c] = cur;
   if (p == -1)
      link[cur] = 0;
   else {
      int q = adj[p][c];
      if (len[p] + 1 == len[q])
         link[cur] = q;
      else {
         int clone = sz++;
         len[clone] = len[p] + 1;
         adj[clone] = adj[q];
         link[clone] = link[q];
         for (; p != -1 && adj[p][c] == q; p = link[p])
            adj[p][c] = clone;
         link[q] = link[cur] = clone;
      }
   }
   last = cur;
}

//Segment Tree

struct SegmentTree{
  int n, t[2 * N];
  int OpId = 0;
  SegmentTree() {}
  int Op(int &u, int &v){ return u + v; }
  void build(){ IFR(i, n - 1, 1) t[i]=Op(t[i << 1], t[i << 1 | 1]); }
  void modify(int p, int val){ for(t[p+=n] = val ; p >>= 1;) t[p] = Op(t[p << 1], t[p << 1 | 1]); }
  int query(int l, int r){
   int ansl, ansr; 
   ansl = ansr = OpId;
   for(l += n, r += n; l < r; l >>= 1, r >>= 1){
      if(l&1) ansl = Op(ansl, t[l++]);
      if(r&1) ansr = Op(t[--r], ansr);
   }
   return Op(ansl, ansr);
  }
};

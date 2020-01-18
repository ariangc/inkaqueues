ll mo;
struct T{
  ll l, r, cur; 
  T(){}
  T(ll l, ll r, ll cur): l(l), r(r), cur(cur){}
};
struct SQRTREE{
  ll n, lg, indexsz;
  vector<T> v;
  vi clz, layers, onlayer;
  vector<vector<T>> pref, suf, between;
  inline T Op(T &val1, T &val2){
    T ty;
    ty.l=val1.l;
    ty.r=val2.r;
    ty.cur=((val1.cur*val2.cur)%mo+mo)%mo;
    return ty;
  }
  inline ll Get(ll n){
    ll ans=0;
    while((1<<ans)<n) ans++;
    return ans;
  }
  inline void preprocess(vector<T> &a){
    n=sz(a), lg=Get(n), v=a;
    clz.resize(1<<lg), onlayer.resize(lg+1);
    FER(i, 0, sz(clz)) clz[i]=(i==0)? 0 : clz[i>>1]+1;
    ll tlg=lg;
    while(tlg>1){
      onlayer[tlg]=sz(layers);
      layers.pb(tlg);
      tlg=(tlg+1)>>1;
    }
    IFR(i, lg-1, 0) onlayer[i]=max(onlayer[i], onlayer[i+1]);
    ll mid=max(0LL, sz(layers)-1);
    ll t=(lg+1)>>1, m=1<<t;
    indexsz=(n+m-1)>>t;
    v.resize(n+indexsz);
    pref.assign(sz(layers), vector<T>(n+indexsz));
    suf.assign(sz(layers), vector<T>(n+indexsz));
    between.assign(mid, vector<T>((1<<lg)+m));
  }
  inline void BuildBlock(ll id, ll l, ll r){
    FER(i, l, r) pref[id][i]=(i==l)? v[i]: Op(pref[id][i-1], v[i]);
    IFR(i, r-1, l) suf[id][i]=(i==r-1)? v[i]: Op(v[i], suf[id][i+1]);
  }
  inline void BuildBetween(ll id, ll l, ll r, ll idx){
    ll t=(layers[id]+1)>>1, m=layers[id]>>1;
    ll ta1=1<<t, len=(r-l+ta1-1)>>t;
    FER(i, 0, len){
      T ans;
      FER(j, i, len){
        T add=suf[id][l+(j<<t)];
        ans=(i==j)? add: Op(ans, add);
        between[id-1][idx+l+(i<<m)+j]=ans;
      }
    }
  }

  inline void BuildZero(){
    ll m=(lg+1)>>1;
    FER(i, 0, indexsz) v[n+i]=suf[0][i<<m];
    build(1, n, n+indexsz, (1<<lg)-n); 
  }
  inline void updZero(ll id){
    ll m=(lg+1)>>1;
    v[n+id]=suf[0][id<<m];
    update(1, n, n+indexsz, (1<<lg)-n, n+id);
  }

  inline void build(ll id, ll l, ll r, ll idx){
    if(id>=sz(layers)) return;
    ll m=1<<((layers[id]+1)>>1);
    for(ll left=l; left<r; left+=m){
      ll right=min(left+m, r);
      BuildBlock(id, left, right);
      build(id+1, left, right, idx);
    }
    id? BuildBetween(id, l, r, idx) : BuildZero();
  }
  inline void update(ll id, ll l, ll r, ll idx, ll p){
    if(id>=sz(layers)) return ;
    ll m=(layers[id]+1)>>1, t=1<<m;
    ll bid=(p-l)>>m;
    ll left=l+(bid<<m), right=min(l+t, r);
    BuildBlock(id, left, right);
    id? BuildBetween(id, l, r, idx): updZero(bid);
    update(id+1, left, right, idx, p);
  }
  inline T query(ll l, ll r, ll idx, ll b){
    if(l==r) return v[l];
    if(l+1==r) return Op(v[l], v[r]);
    ll id=onlayer[clz[(l-b) ^ (r-b)]];
    ll t=(layers[id]+1)>>1, m=layers[id]>>1;
    ll in=(((l-b)>>layers[id])<<layers[id])+b;
    ll left=((l-in)>>t)+1, right=((r-in)>>t)-1;
    T ans=suf[id][l];
    if(left<=right){
      ll idd=idx+in+(left<<m)+right;
      T add=(id==0)? query(n+left, n+right, (1<<lg)-n, n):between[id-1][idd];
      ans=Op(ans, add);
    }
    ans=Op(ans, pref[id][r]);
    return ans;
  }
  inline T que(ll l, ll r){
    return query(l, r, 0, 0);
  }
  inline void upd(ll p, T val){
    v[p]=val;
    update(0, 0, n, 0, p);
  }
  inline void build(){
    build(0, 0, n, 0);
  }
};
ll queries[N];
int main(){
  fastio;
  ll t; cin>>t;
  FER(ikl, 0, t){  
    SQRTREE sqrtree;
    ll n, q; cin>>n>>mo>>q;
    vector<T> a;
    FER(i, 0, n){
      T x;
      cin>>x.cur;
      x.l=i, x.r=i;
      a.pb(x);
    }
    sqrtree.preprocess(a);
    sqrtree.build();
    ll q1=(q>>6)+2;
    ll l, r;
    FER(i,0,q1) cin>>queries[i];
    ll ja=0;
    FER(i, 0, q){
      (i%(1<<6))? (l=(l+ja)%n, r=(r+ja)%n): (l=(queries[i>>6]+ja)%n, r=(queries[(i>>6)+1]+ja)%n);
      if(l>r) swap(l, r);
      ja=(sqrtree.que(l, r).cur+1)%mo;
    }
    cout<<ja<<"\n";
  }
  return 0;
}

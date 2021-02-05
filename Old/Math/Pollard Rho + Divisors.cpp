/* Pollard Rho + Recursive Divisors
   Autor: Phibrain
*/

const int maxp = 1e6 + 1, maxv = 25, maxc = (int)1e4 + 1;
int ptot, pr[maxp], d[maxp], cnt;
ll p[maxc];
inline ll mod_add(ll x, ll y, ll p) {
  return (x += y) < p ? x : x - p;
}
inline ll mod_mul(ll x, ll y, ll p) {
  ll ret = x * y - (ll)((long double)x * y / p + 0.5) * p;
  return ret < 0 ? ret + p : ret;
}
inline ll mod_pow(ll x, ll k, ll p) {
  ll ret = 1 % p;
  for( ; k > 0; k >>= 1, x = mod_mul(x, x, p))
   (k & 1) && (ret = mod_mul(ret, x, p));
  return ret;
}
bool miller_rabin(ll n) {
  if(n == 2) return 1;
  if(n < 2 || !(n & 1))
   return 0;
  ll s = 0, r = n - 1;
  for( ; !(r & 1); r >>= 1, ++s);
  for(int i = 0; pr[i] < n && pr[i] < maxv; ++i) {
   ll cur = mod_pow(pr[i], r, n), nxt;
   for(int j = 0; j < s; ++j) {
     nxt = mod_mul(cur, cur, n);
     if(nxt == 1 && cur != 1 && cur != n - 1) return 0;
     cur = nxt;
   }
   if(cur != 1) return 0;
  }
  return 1;
}
inline ll gcd(ll a, ll b) {
  int ret = 0;
  while(a) {
   for( ; !(a & 1) && !(b & 1); ++ret, a >>= 1, b >>= 1);
   for( ; !(a & 1); a >>= 1);
   for( ; !(b & 1); b >>= 1);
   if(a < b)
     swap(a, b);
   a -= b;
  }
  return b << ret;
}
inline ll pollard_rho(ll n) {
  static ll seq[maxp];
  while(1) {
   ll x = rand() % n, y = x, c = rand() % n;
   ll *px = seq, *py = seq, tim = 0, prd = 1;
   while(1) {
     *py++ = y = mod_add(mod_mul(y, y, n), c, n);
     *py++ = y = mod_add(mod_mul(y, y, n), c, n);
     if((x = *px++) == y) break;
     ll tmp = prd;
     prd = mod_mul(prd, abs(y - x), n);
     if(!prd) return gcd(tmp, n);
     if((++tim) == maxv) {
      if((prd = gcd(prd, n)) > 1 && prd < n) return prd;
      tim = 0;
     }
   }
   if(tim && (prd = gcd(prd, n)) > 1 && prd < n) return prd;
  }
}
inline void decompose(ll n) {
  for(int i = 0; i < cnt; ++i)
   if(n % p[i] == 0) {
     p[cnt++] = p[i];
     n /= p[i];
   }
  if(n < maxp) {
   for( ; n > 1; p[cnt++] = d[n], n /= d[n]);
  } else if(miller_rabin(n)) {
   p[cnt++] = n;
  } else {
   ll fact = pollard_rho(n);
   decompose(fact), decompose(n / fact);
  }
}
inline void build(){
  FER(i, 2, maxp) {
   if(!d[i]) pr[ptot++] = d[i] = i;
   for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
     d[k] = pr[j];
     if(d[i] == pr[j]) break;
   }
  }   
} 
inline void construct(vii &v){
  sort(p, p+cnt);
  for(int i = 0; i < cnt; ) {
   ll ctr=0;
   for(ll pp = p[i]; i < cnt && p[i] == pp; ++i, ++ctr);
   v.pb({p[i-1], ctr});
  }
  cnt=0;
}
inline void make(ll n){
  decompose(n);
}
vi froz[N], v[N];
ll ja;
inline void go(ll n, ll t, vi &tt){
   if(n>=t){
      for(auto xd: tt) froz[ja].pb(xd);
      ja++;
      tt.pop_back();
      return;
   }
   FER(i,0,sz(v[n])){
      tt.pb(v[n][i]);
      go(n+1, t, tt);
   }
   if(sz(tt)) tt.pop_back();
}

inline void solve(ll t){
   vi tt;
   go(0, t, tt);
}

inline void kotaro(ll n, vi &v){
   FER(i, 0, n){
      ll t = 1;
      for(auto xd: froz[i]) t *= xd;
      v.pb(t);
   }
}

int main(){
   build();
   ll n; cin>>n;
   make(n);
   vii v1;
   construct(v1);
   cout<<"La factorizacion es: "<<endl;
   for(auto xd: v1){
      cout<<xd.ff<<" "<<xd.ss<<endl;
   }
   cout<<"Los divisores son: "<<endl;
   ja=0;
   FER(i,0,sz(v1)){
      ll t=1;
      ll ta=v1[i].ss+1, num=v1[i].ff;
      FER(j,0,ta) {
         v[i].pb(t);
         t*=v1[i].ff;
      }
   }
   solve(sz(v1));
   vi tnt;
   kotaro(ja, tnt);
   sort(all(tnt));
   for(auto xd: tnt) cout<<xd<<" "; cout<<endl;
   return 0;
}

//FFT

#define pi acos(-1)
struct cpx{
   double a, b;
   cpx() : a(0.0), b(0.0){}
   cpx(double a, double b) : a(a), b(b){}
   const cpx operator+(const cpx &c) const{return cpx(a+c.a, b+c.b);}
   const cpx operator-(const cpx &c) const{return cpx(a-c.a, b-c.b);}
   const cpx operator*(const cpx &c) const{return cpx(a*c.a-b*c.b, a*c.b+b*c.a);}
};
struct FFT{
   vector<cpx> data, roots;
   vi rev;
   ll s, n;
   inline void init(ll pw){
      s=pw, n=(1<<s);
      rev=vi(n), data=vector<cpx> (n), roots=vector<cpx> (n+1);
      FER(i,0,n) FER(j,0,s) if((i & (1<<j))!=0) rev[i]+=(1<<(s-j-1));
      roots[0]=cpx(1, 0);
      cpx mult=cpx(cos(2*pi/n), sin(2*pi/n));
      FER(i,1,n+1) roots[i]=roots[i-1]*mult;
   }
   inline void transform(bool inverse=false){
      vector<cpx> temp(n);
      FER(i,0,n) temp[i]=data[rev[i]];
      FER(i,0,n) data[i]=temp[i];
      FER(i,1,s+1){
         ll m=(1<<i), md2=m/2;
         ll start=0, incr=(1<<(s-i));
         cpx t;
         if(inverse) start=n, incr*=-1;
         for(ll k=0; k<n; k+=m){
            ll idx=start;
            FER(j,k,md2+k){
               t=roots[idx]*data[j+md2];
               idx+=incr;
               data[j+md2]=data[j]-t;
               data[j]=data[j]+t;
            }
         }
      }
      if(inverse) FER(i,0,n) data[i].a/=n, data[i].b/=n;
   }
};
inline void build(vi &a, FFT &f, ll y, ll n){
   f.init(y);
   FER(i, 0, sz(a)) f.data[i]=cpx(a[i], 0);
   FER(i,sz(a), n) f.data[i]=cpx(0, 0);
   f.transform();
}
inline vi GetConvolution(vi &a, vi &b){
   ll t1=sz(a), t2=sz(b), ta=t1+t2-1, x=0, n;
   while((1<<x)<ta) x++;
   n=1<<x;
   FFT f1, f2;
   build(a, f1, x, n), build(b, f2, x, n);
   FER(i,0,n) f1.data[i]=f1.data[i]*f2.data[i];
   f1.transform(true);
   vi froz(ta);
   FER(i,0,ta) froz[i]=(ll) (f1.data[i].a+0.5);
   return froz;
}
int main(){
   fastio;
   ll t; cin>>t;
   while(t--){
      ll n; cin>>n;
      vi v1, v2;
      FER(i,0,n+1){
         ll x; cin>>x;
         v1.pb(x);
      }
      FER(i,0,n+1) {
         ll x; cin>>x;
         v2.pb(x);
      }
      vi c=GetConvolution(v1, v2);
      for(auto xd: c) cout<<xd<<" "; cout<<endl;
   }
   return 0;
}

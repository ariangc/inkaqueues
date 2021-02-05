
void sum(ll &a, ll b){
   a += b;
   if(a >= MOD) a -= MOD;
}
 
void Init(ll a[N][N]){
   FER(i,0,N) FER(j,0,N) a[i][j] = (i == j);
}
 
void Cpy(ll a[N][N], ll b[N][N]){
   FER(i,0,N) FER(j,0,N) b[i][j] = a[i][j];
}
 
void Mult(ll a[N][N], ll b[N][N], ll c[N][N]){
   FER(i,0,N) FER(j,0,N) c[i][j] = 0;
   FER(i,0,N) FER(j,0,N) FER(k,0,N)
      sum(c[i][j],(a[i][k]*b[k][j])%MOD);
}
 
void BinPow(ll a[N][N], ll p, ll ans[N][N]){
   ll aux[N][N]; Init(ans);
   while(p){
      if(p&1LL) Mult(ans,a,aux), Cpy(aux,ans);
      p >>= 1; Mult(a,a,aux); Cpy(aux,a);
   }
}

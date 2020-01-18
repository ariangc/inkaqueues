// Given a, b and m, fin a value "x" that 
// a^x=(b)mod(m)
// Complexity in sqrt(m)

inline ll GetExpo(ll a, ll b, ll c){
    ll n=sqrt(c)+1;
    ll ans=1, cur;
    map<ll, ll> m;
    FER(i,1,n+1) ans=(ans*a)%c;
    cur=ans;
    FER(i,1,n+1){
        if(!m[cur]) m[cur]=i;
        cur=(cur*ans)%c;
    }
    cur=b;
    FER(i,0,n){
        if(m[cur]){
        	return m[cur]*n-i;
        }
        cur=(cur*a)%c;
    }
}
 
int main(){
    fastio;
    ll t, ans; cin>>t;
    while(t--){
        ll a, b, m; cin>>a>>b>>m;
        if(a==b%m) {cout<<1<<endl; continue;}
        if(b==1 && m!=1) {cout<<0<<endl; continue;}
        ans=GetExpo(a, b, m);
        cout<<ans<<endl;
    }
    return 0;
}
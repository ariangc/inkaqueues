// URI 2698 - Daunting Device (ICPC LATAM 2017)

// Remember: Check array size, use scanf/printf, corner cases, read statement
#pragma GCC optimize ("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define REP(i,a,b) for(int i = (int)(a); i < (int)(b); ++ i)
#define pb push_back
#define sz(x) (int)(x.size())
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> ii;
typedef long double ld;
 
const int N = 1e5 + 2;
const int oo = 1e9;
const int Mod = 1e9 + 7;

typedef array<int,3> T;

struct IntervalSet{
	set<T> st;
	int cnt[N];

	void insert(int from, int to, int p){
		vector<T> toer;
		auto it = st.upper_bound({to,oo,oo}); // +1 combinar consecutivos
		while(it != st.begin()){
			it --;
			T x = *it;
			if(x[1] < from) break; // +1
			toer.pb(x);
		}
		for(auto x: toer){
			st.erase(x);
			from = min(x[0], from), to = max(x[1], to);
			cnt[x[2]] -= x[1] - x[0] + 1;
		}
		st.insert({from,to,p});
		cnt[p] += to - from + 1;
	}

	void remove(int from, int to){
		vector<T> toer;
		auto it = st.upper_bound({to,oo,oo}); // +1
		if(it == st.begin()) return;
		while(it != st.begin()){
			it --;
			T x = *it;
			if(x[1] < from) break; // +1
			toer.pb(x);
		}
		for(auto x: toer){
			st.erase(x);
			cnt[x[2]] -= x[1] - x[0] + 1;
			if(x[1] > to) st.insert({to+1, x[1], x[2]}), cnt[x[2]] += x[1] - to;
			if(x[0] < from) st.insert({x[0], from-1, x[2]}), cnt[x[2]] += from - x[0];
		}
	}

}ist;

int main(){
	fastio;
	int l,c,n; cin >> l >> c >> n;
	ist.insert(0,l-1,1);
	REP(i,0,n){
		int p,x,a,b; cin >> p >> x >> a >> b;
		int s = ist.cnt[p];
		int m1 = (1LL * a + 1LL * s * s) % l;
		int sum = (s + b) % l;
		int m2 = (1LL * a + 1LL * sum * sum) % l;
		if(m1 > m2) swap(m1, m2);
		ist.remove(m1,m2);
		ist.insert(m1,m2,x);
	}
	int high = 0;
	REP(i,0,N) high = max(high, ist.cnt[i]);
	cout << high << endl;
	return 0;
}

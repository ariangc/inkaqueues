// Suffix Array - Gracias Itu
// Complejidad: O(nlog^2n). Usualmente es rápido (0.6s ~ N = 10^6)
//	Los caracteres dollar deben tener MENOR valor que el alfabeto
//	y deben ser diferentes entre ellos.
// usage:
//		Llenar s[N] y asignar n. 
//		suff_arr(): Construye el suffix array en p y r.
//			-> r es el suffix array, i.e. r[i] es el inicio del sufijo i.
//			-> p[i] es el orden (posicion en r) del sufijo que inicia en i.

const int N = 1000010;  
const int LG = 25;

struct SuffixArray{
	int n,t;
	int p[N],r[N],h[N];    
	char s[N];                   
	int rmq[LG][N];
	int flog2[N];

	void fix_index(int b, int e){
		int lastpk, pk, d;
		lastpk = p[r[b]+t];
		d = b;
		FER(i,b,e){
			if (((pk = p[r[i]+t]) != lastpk) 
				&& (b > lastpk || pk >= e)){
				lastpk = pk;
				d = i;
			}
			p[r[i]]= d;
		}
	}

	// Computes the r and p in O(n*log^2(n))
	void suff_arr(){
		int bc[256];
		FER(i,0,256) bc[i]=0;
		FER(i,0,n) bc[(int)s[i]]++;
		FER(i,1,256) bc[i] += bc[i-1];
		for (int i = n-1; i >= 0; i--) r[--bc[(int)s[i]]] = i;
		for (int i = n-1; i >= 0; i--) p[i] = bc[(int)s[i]];
		for (t = 1; t < n; t<<=1){
			for (int i = 0, j = 1; i < n; i = j++){
				while (j < n && p[r[j]] == p[r[i]]) ++j;
				if (j-i > 1){
					sort(r+i, r+j, [&](const int& i, const int& j){
						return p[i+t] < p[j+t];
					});
					fix_index(i, j);        
				}
			}
		}
	}

	// Computes the LCP array in O(n) by Kasai-LCP
	void initlcp(){
		int tam = 0, j;
		FER(i,0,n-1){
			j = r[p[i]-1];
			while(s[i+tam] == s[j+tam]) ++tam;
			h[p[i]-1] = tam;
			if (tam > 0) --tam;
		}
	}

	// Creates the full LCP by RMQ in O(n*log(n))
	void makelcp(){
		initlcp();
		FER(i,0,n-1) rmq[0][i] = h[i];
		int lg = 0, pw = 1;
		do{
			FER(i,pw,pw*2) flog2[i] = lg;
			lg++; pw*=2;
			FER(i,0,n-1){
				if (i+pw/2 < n-1) 
					rmq[lg][i] = min(rmq[lg-1][i], rmq[lg-1][i+pw/2]);
				else 
					rmq[lg][i] = rmq[lg-1][i];
			}
		}while(pw < n);
	}

	// LCP in interval [i,j] of the suffix array
	int lcp(int i, int j){
		if (i == j) return n - r[i] - 1;
		int lg = flog2[j-i], pw = (1<<lg);
		return min(rmq[lg][i], rmq[lg][j-pw]);
	}

	void clear(){
		fill(p, 0); fill(r, 0); fill(h, 0);
		fill(rmq, 0); fill(flog2, 0);
	}
};


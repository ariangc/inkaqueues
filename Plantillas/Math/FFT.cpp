// Fast Fourier Transform - Gracias Vladislao
// Operaciones de FFT para +-*/ de polinomios
// usage:
//		Crear polinomios del tipo Poly
//		add(p1,p2): Suma de polinomios
//		mult(p1,p2): Multiplicacion con FFT
//		invert(p,d): Calcular la inversa polinommial de p con d terminos
//		divide(p1,p2): Division de polinomios
//		multi_evaluate(p1,vec): Multievaluacion de p1 en valores vec

const double PI = acos(-1);
const int N = (1 << 17);

struct Cpx{
	double r, i;
	Cpx(double r = 0, double i = 0): r(r), i(i){}
	double real() const{ return r; }
	void operator /= (const int c){ r /= c, i /= c;}
};

Cpx operator * (const Cpx &a, const Cpx &b){return Cpx(a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r);}
Cpx operator + (const Cpx &a, const Cpx &b){return Cpx(a.r + b.r, a.i + b.i);}
Cpx operator - (const Cpx &a, const Cpx &b){return Cpx(a.r - b.r, a.i - b.i);}

Cpx cp1[N+9], cp2[N+9];
int R[N+9];

void fft(Cpx *a, int n, bool inv){
	REP(i,0,n) if(R[i] < i) swap(a[R[i]], a[i]);
	for(int m = 2; m <= n; m *= 2){
		double z = 2 * PI / m * (inv ? -1 : 1);
		Cpx wi = Cpx(cos(z), sin(z));
		for(int j = 0; j < n; j += m){
			Cpx w(1);
			for(int k = j, k2 = j + m/2; k2 < j + m; k ++, k2 ++){
				Cpx u = a[k]; Cpx v = a[k2] * w;
				a[k] = u + v, a[k2] = u - v;
				w = w * wi;
			}
		}
	}
	if(inv) REP(i,0,n) a[i] /= n;
}

typedef vector<ld> Poly;

Poly add(Poly &p1, Poly &p2){
	int high = max(sz(p1), sz(p2));
	Poly res(high, 0);
	REP(i,0,high) {
		if(i < sz(p1)) res[i] += p1[i];
		if(i < sz(p2)) res[i] += p2[i];
	}
	return res;
}

Poly mul(Poly &p1, Poly &p2){
	int n = sz(p1) + sz(p2) + 1;
	int m = 1, cnt = 0;
	while(m <= n) m += m, cnt ++;
	REP(i,0,m){ R[i] = 0; REP(j,0,cnt) R[i] = (R[i] << 1) | ((i >> j) & 1); }
	REP(i,0,m) cp1[i] = 0, cp2[i] = 0;
	REP(i,0,sz(p1)) cp1[i] = p1[i];
	REP(i,0,sz(p2)) cp2[i] = p2[i];
	fft(cp1, m, false); fft(cp2, m, false);
	REP(i,0,m) cp1[i] = cp1[i] * cp2[i];
	fft(cp1, m, true);
	Poly res;
	n -= 2;
	REP(i,0,n){ res.pb((ll)floor(cp1[i].real() + 0.5));}
	return res;
}

Poly invert(Poly &b, int d){
	if(d == 0){
		return Poly(1, 1.0L / b[0]);
	}
	Poly c = invert(b, d/2);
	Poly cb = mul(c, b);
	cb[0] = 2.0L - cb[0];
	REP(i,1,sz(cb)) cb[i] = -cb[i];
	Poly q = mul(c, cb);
	return q;
}

pair<Poly, Poly> divide(Poly &a, Poly &b){
	int m = sz(a), n = sz(b);
	if(n > m){
		return {Poly(1,0), a};
	}	
	Poly at = a, bt = b;
	reverse(at.begin(), at.end());
	reverse(bt.begin(), bt.end());

	bt = invert(bt, m - n);

	Poly q = mul(at, bt);
	
	q.resize(m - n + 1, 0);
	reverse(q.begin(), q.end());

	Poly bq = mul(b, q);
	REP(i,0,sz(bq)) bq[i] = -bq[i];
	Poly r = add(a, bq);

	return {q, r};
}

vector<Poly> t;

void fill_tree(vector<ll> &x){
	int n = sz(x);
	t.resize(2 * n);
	REP(i,0,n) t[i+n] = Poly(2,1), t[i+n][0] = -x[i];
	for(int i = n - 1; i >= 1; --i) t[i] = mul(t[i << 1], t[i << 1 | 1]);
}

vector<ll> multi_evaluate(Poly &a, vector<ll> &x){
	fill_tree(x);
	int n = sz(x);
	vector<Poly> ans(2*n);
	ans[1] = divide(a, t[1]).ss;
	REP(i,2,2*n) ans[i] = divide(ans[i >> 1], t[i]).ss;
	vector<ll> ret(n);
	REP(i,0,n) ret[i] = ans[i+n][0];
	return ret;
}

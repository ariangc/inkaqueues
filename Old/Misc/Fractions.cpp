struct Frac{
	ll a,b;
	Frac(){}
	Frac(ll _a, ll _b) : a(_a), b(_b){
		if(b < 0) a = -a, b = -b;
	}
	void toZero(){ a = 0; }
	long double getReal(){ return (long double)a / b; }
	Frac operator * (ll x){ return Frac(a*x,b); }
	Frac operator + (Frac other){
		return Frac(a*other.b + b * other.a,b * other.b);
	}
	bool positive(){ return a > 0;}
	bool negative(){ return a < 0;}
	bool operator == (Frac &other){
		return a * other.b == b * other.a;
	}
	bool operator < (const Frac &other) const{
		return a * other.b < b * other.a;
	}
	bool operator > (const Frac &other) const{
		return a * other.b > b * other.a;
	}
	bool operator <= (const Frac &other) const{
		return a * other.b <= b * other.a;
	}
	bool operator >= (const Frac &other) const{
		return a * other.b >= b * other.a;
	}
};

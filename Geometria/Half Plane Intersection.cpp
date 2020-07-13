const ld eps=1e-8;

struct pt{
	ld x,y;
	pt():x(0),y(0){}
	pt(ld x,ld y):x(x),y(y){}
	pt(const pt& p):x(p.x),y(p.y){}
	void read(){cin>>x>>y;}
	void print(){cout<<x<<" "<<y<<endl;}
}zero;

pt operator + (pt a,pt b){return pt(a.x+b.x,a.y+b.y);}
pt operator - (pt a,pt b){return pt(a.x-b.x,a.y-b.y);}
pt operator * (pt a,ld d){return pt(a.x*d,a.y*d);}
pt operator / (pt a,ld d){return pt(a.x/d,a.y/d);}
ld operator * (pt a,pt b){return a.x*b.x+a.y*b.y;}
ld operator ^ (pt a,pt b){return a.x*b.y-a.y*b.x;}

ld torque(pt a,pt b,pt c){return (b-a)^(c-a);}
int orient(pt a,pt b,pt c){
	ld val=torque(a,b,c);
	return (val<-eps)?-1:val>eps;
}

bool parallel(pt a,pt b){
	return orient(zero,a,b)==0;}

struct half{
	pt a,b;
	half(){}
	half(const pt& a,const pt &b):a(a),b(b){}
	pt v(){return b-a;}
	bool operator <(half H)const{
		ld t1=atan2((b-a).y,(b-a).x);
		ld t2=atan2((H.b-H.a).y,(H.b-H.a).x);
		if(fabs(t1-t2)>eps)return t1<t2;
		return orient(a,H.a,H.b)>0;
	}
};

pt intersect(half A,half B){
	pt a=A.a,b=A.b,c=B.a,d=B.b;
	b=b-a;d=d-c;
	ld lamb=((c-a)^d)/(b^d);
	return a+b*lamb;
}

bool ter(vector<pt>&P,int n,int &l,int &r){
	vector<half>H(n),Q(n);
	For(i,0,n)H[i].a=P[i],H[i].b=P[i+1];
	sort(all(H));
	For(i,0,n)if(i==0||!parallel(H[i].v(),H[i-1].v())){
		while(l<r&&orient(P[r],H[i].a,H[i].b)<0)r--;
		while(l<r&&orient(P[l+1],H[i].a,H[i].b)<0)l++;
		Q[++r]=H[i];
		if(r-l==1&&parallel(Q[r].v(),Q[l].v()))return false;
		if(l<r)P[r]=intersect(Q[r],Q[r-1]);
	}
	while(l<r&&orient(P[r],Q[l].a,Q[l].b)<0)r--;
	if(r-l==1)return false;
	P[r+1]=intersect(Q[l],Q[r]);r++;
	return true;
}

ld area(vector<pt>&P,int l,int r){
	P[++r]=P[l+1];
	ld ans=0;
	for(int i=l+1;i<r;i++)ans+=P[i]^P[i+1];
	if(ans<0)ans*=-1;
	return ans/2;
}

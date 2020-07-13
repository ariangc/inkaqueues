typedef vector<vector<ld> > matrix;

const ld eps=1e-10;

//puede dar como solucion -0.00 (cuidado)
//inicializa x como:
//matrix x(sz(a[0]),vector<ld>(X,0.0L));
//donde x depdende de cuantos vectores se quieren resolver
//con b=I se puede calcular la inversa
vector<bool>solve(matrix &a,matrix &b,matrix &x){
	// row reduced echelon form
	int n=sz(a),m=sz(a[0]);
	int n2=sz(b),m2=sz(b[0]);
	vector<int>where(m,-1);
	for(int col=0,row=0;col<m&&row<n;col++){
		int sel=row;
		For(i,row,n)
			if(abs(a[i][col])>abs(a[sel][col]))
				sel=i;
		if(abs(a[sel][col])<eps)continue;
		For(i,col,m)swap(a[sel][i],a[row][i]);
		For(i,0,m2)swap(b[sel][i],b[row][i]);
		where[col]=row;
		For(i,0,n)if(i!=row){
			ld c=a[i][col]/a[row][col];
			For(j,col,m)a[i][j]-=a[row][j]*c;
			For(j,0,m2)b[i][j]-=b[row][j]*c;
		}
		row++;
	}
	// assign
	vector<bool>has(m2,true);
	For(col,0,m2)For(i,0,m)if(where[i]!=-1)
		x[i][col]=b[where[i]][col]/a[where[i]][i];
	For(col,0,m2)For(i,0,n){
		ld sum=0;
		For(j,0,m)sum+=x[j][col]*a[i][j];
		if(abs(sum-b[i][col])>eps)has[col]=false;
	}
	return has;
}

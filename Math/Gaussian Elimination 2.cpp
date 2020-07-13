// see debe ser true para confiar del valor
// notar que ya no se computa rref, puede mejorar la precision

void solve(matrix &a,matrix &b,matrix &x,
				vector<vector<bool> >&see){
	int n=sz(a),m=sz(a[0]);
	int n2=sz(b),m2=sz(b[0]);
	vector<int>where(n,-1);
	vector<int>wherecol(m,-1);
	for(int col=0,row=0;col<m&&row<n;col++){
		int sel=row;
		For(i,row,n)
			if(fabs(a[i][col])>fabs(a[sel][col]))
				sel=i;
		if(fabs(a[sel][col])<eps)continue;
		For(i,col,m)swap(a[sel][i],a[row][i]);
		For(i,0,m2)swap(b[sel][i],b[row][i]);
		where[row]=col;
		wherecol[col]=row;
		For(i,row+1,n)if(i!=row){
			ld c=a[i][col]/a[row][col];
			For(j,col,m)a[i][j]-=a[row][j]*c;
			For(j,0,m2)b[i][j]-=b[row][j]*c;
		}
		row++;
	}
	roF(eq,n-1,0)if(where[eq]!=-1){
		int cnt=0;
		For(var,0,m)if(fabs(a[eq][var])>eps
			&&wherecol[var]==-1)cnt++;
		if(!cnt){
			For(sol,0,m2){
				ld tmp=b[eq][sol];
				For(var,0,m)if(var!=where[eq]){
					if(fabs(a[eq][var])<eps)continue;
					tmp-=a[eq][var]*x[var][sol];
				}
				x[where[eq]][sol]=tmp/a[eq][where[eq]];
				if(fabs(x[where[eq]][sol])<eps)
					x[where[eq]][sol]=0.0L;
				see[where[eq]][sol]=true;
			}
		}
		else wherecol[where[eq]]=-1;
	}
}

/* Matrix Determinant */

ll matrix[1<<8][1<<8];
 
inline ll FindDeterminant(ll n, ll m){
   FER(i,0,n) FER(j,0,n) {
      matrix[i][j]%=m;
      matrix[i][j]+=m;
      if(matrix[i][j]>=m) matrix[i][j]-=m;
   }
   ll res=1;
   FER(i,0,n){
      if(!matrix[i][i]){
         bool flag=false;
         FER(j,i+1,n){
            if(matrix[j][i]){
               flag=true;
               FER(k,i,n) swap(matrix[i][k], matrix[j][k]);
               res=-res;
               break;
            }
         }
         if(!flag) return 0;
      }
      FER(j,i+1,n){
         while(matrix[j][i]){
            ll t=matrix[i][i]/matrix[j][i];
            FER(k,i,n){
               matrix[i][k]=(matrix[i][k]-
                  t*matrix[j][k])%m;
               swap(matrix[i][k], matrix[j][k]);
            }
            res=-res;
         }
      }
      res=(res*matrix[i][i])%m;
   }
   return (res+m)%m;
}

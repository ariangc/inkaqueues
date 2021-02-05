//Divide and Conquer Trick
//Solves dp[i][j] = min k < j {dp[i - 1][k] + C[k][j]}
//Think about the base cases and set them on main
//The most important part is to set the method for getval
//Hint: Should be some dp or segment tree

void go(ll i, ll l, ll r, ll optl, ll optr){
	if(l >= r) return;
    ll m = (l + r) >> 1;
    ll opt = -1;
    dp[i][m] = -1;
    FER(k, optl, min(optr, m) + 1){
        ll c = dp[i-1][k] + getval(k + 1, m + 1);
        if(c > dp[i][m]){
            dp[i][m] = c; opt = k;
        }
    }
    go(i, l, m, optl, opt);
    go(i, m + 1, r, opt, optr);
}

int main(){
    FER(i, 0, n) dp[0][i] = //base cases!;
	FER(i, 1, m) go(i, 0, n , 0, n);
	cout << dp[m - 1][n - 1] << endl;
	return 0;
}

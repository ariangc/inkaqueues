/* Chinese remainder theorem.
     Find z such that  z % x[i] = a[i] for all i.
*/
ll crt(vector<ll> &a, vector<ll> &x) {
  ll z = 0;
  ll n = 1;
  for (int i = 0; i < x.size(); ++i)
   n *= x[i];

  for (int i = 0; i < a.size(); ++i) {
   ll tmp = (a[i] * (n / x[i])) % n;
   tmp = (tmp * mod_inv(n / x[i], x[i])) % n;
   z = (z + tmp) % n;
  }

  return (z + n) % n;
} 

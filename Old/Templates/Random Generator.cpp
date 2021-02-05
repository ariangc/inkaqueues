//Mersenne Twister Random Generator
//Note: If you want 64-bit random numbers, 
//     just declare it as mt19937_64.

mt19937 rng(chrono::steady_clock::now().
         time_since_epoch().count());

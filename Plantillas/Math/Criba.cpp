// comment

bool done[N];

void sieve(){
	//codeas algo
	for(int i = 2; i <= N; ++ i){
		if(!done[i]){
			for(int j = i*i; j <= N; j += i) done[j] = true;
		}
	}
}

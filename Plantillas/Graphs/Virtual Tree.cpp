// Construccion del Virtual Tree en O(klog(k))
// Se necesita la implementacion del LCA
// usage:
//		buildTree(vert): Construir el VT de los vertices en vert.
//							  Retorna la raiz.

vector<int> g[N]; //Virtual Tree

//st and en are the dfs start and end time (precompute in lca implementation)

bool above(int &u, int &v){ //This also serves lca implementation
	if(u == -1) return true;
	return st[u] <= st[v] && en[u] >= en[v];
}

bool cmp(int &u, int &v){ return st[u] < st[v]; }

int buildTree(vector<int> &vert){ //Returns root of vtree
	sort(vert.begin(), vert.end(), cmp);
	int size = sz(vert);
	for(int i = 0; i < size - 1; ++ i){
		vert.pb(lca(vert[i], vert[i + 1]));
	}
	sort(vert.begin(), vert.end(), cmp);
	vert.erase(unique(vert.begin(), vert.end()), vert.end());
 
	for(int x: vert) g[x].clear();
	
	vector<int> stk;
	stk.pb(vert[0]);
	for(int i = 1; i < sz(vert); ++ i){
		while(sz(stk) >= 2 && !above(stk.back(), vert[i])){
			g[stk[sz(stk) - 2]].pb(stk.back());
			stk.pop_back();
		}
		stk.pb(vert[i]);
	}
	while(sz(stk) >= 2){
		g[stk[sz(stk) - 2]].pb(stk.back());
		stk.pop_back();
	}
	return stk.top();
}

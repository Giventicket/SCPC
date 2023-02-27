#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define MAXN 100001
#define MAXK 200001
typedef long long int ll;

int N, K;
vector<int> parent, sz;
vector<ll> diff;
vector<bool> cf;
vector<set<int>> st;
set<int>::iterator it;

int find(int u) {
	if (parent[u] == u)
		return u;
	return parent[u] = find(parent[u]);
}

void merge(int u, int v, ll val) {
	/*
	should satisfy the condition: sz[u] <= sz[v]
	put root of u into root of v: parent[u] = v
	renew sz, diff, st, ...
	*/
	
	int uu = find(u);
	int vv = find(v);
	
	if (uu == vv)
		return;
	
	if (sz[uu] > sz[vv]) {
		merge(v, u, -val);
		return;
	}
	
	//parent[uu] = vv;
	sz[vv] += sz[uu];
	cf[vv] = (cf[vv] | cf[uu]); 
	ll del = diff[v] - diff[u] + val;
	for (it = st[uu].begin(); it != st[uu].end(); it++) {
		int idx = (*it);
		/*
		let's define: diff[a] = val[a] - val[find(a)].
		*/
		diff[idx] += del; 
		parent[idx] = vv;
		st[vv].insert(idx);
	}
	st[uu].clear();
	return;
}

void input() {
	cin >> N >> K;
	
	parent.clear();
	sz.clear();
	diff.clear();
	cf.clear();
	st.clear();
	
	parent.resize(2 * MAXN);
	sz.resize(2 * MAXN);
	diff.resize(2 * MAXN);
	cf.resize(2 * MAXN);
	st.resize(2 * MAXN);
	
	for (int i = 0; i < 2 * MAXN; i++)
		parent[i] = i, sz[i] = 1, diff[i] = 0, st[i].insert(i), cf[i] = false;
	
	int op, u, v;
	ll val;
	for (int i = 0; i < K; i++) {
		cin >> op;
		switch (op) {
			case 1:
				cin >> u >> v >> val;
				if (find(u) == find(v)) {
					if (diff[u] - diff[v] != val) {
						//cout << "conflict " << u << " " << v << " " << diff[u] << " " << diff[v] << endl;
						cf[find(u)] = true;
					}
				} else
					merge(u, v, val);
				break;
			case 2:
				cin >> u >> v;
				if (find(u) != find(v))
					cout << "NC\n";
				else if (cf[find(u)])
					cout << "CF\n";
				else
					cout << diff[u] - diff[v] << "\n";
				break;
		}
	}
	
	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
	}
	
	return 0;
}

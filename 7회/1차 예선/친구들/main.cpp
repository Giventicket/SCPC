#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int N;
vector<int> root;
vector<int> Rank;
vector<int> D;

int find(int x) {
    if (root[x] == x)
        return x;
	return root[x] = find(root[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
	
	if (x == y)
		return;
	
	if (Rank[x] < Rank[y]) {
		merge(y, x);
		return;
	} else if (Rank[x] == Rank[y])
		Rank[x]++;
	
    root[y] = x;
}

void input() {
	cin >> N;
	
	root.clear();
	Rank.clear();
	D.clear();
	root.resize(N);
	Rank.resize(N);
	D.resize(N);
	
	for (int i = 0; i < N; i++) {
		root[i] = i;
		Rank[i] = 0;
		cin >> D[i];
	}
	
	return;
}

void solve() {
	for (int i = 0; i < N; i++) {
		if (i + D[i] < N)
			merge(i, i + D[i]);
	}
	set<int> st;
	for(int i = 0; i < N; i++)
		st.insert(find(i));
	cout << st.size() << "\n";
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
		// inputs
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}

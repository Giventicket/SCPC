#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int N, M, K;
vector<vector<int>> adj;
vector<pair<int, int>> query;
int cnt;
vector<int> dfscnt;
vector<bool> finished;

void input() {
	adj.clear();
	query.clear();
	
	cin >> N >> M >> K;
	
	adj.resize(N + 1);
	query.resize(K);
	
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
	
	for (int i = 0; i < K; i++) 
		cin >> query[i].first >> query[i].second;
	
	return;
}

void dfs(int u, bool &hasCycle) {
	dfscnt[u] = cnt++;
	for (int v: adj[u]) {
		if (dfscnt[v] == -1)
			dfs(v, hasCycle);
		else if (dfscnt[v] < dfscnt[u] && !finished[v])
			hasCycle = true;
	}
	finished[u] = true;
	return;
}

bool getHasCycle() {
	cnt = 0;
	dfscnt = vector<int>(N + 1, -1);
	finished = vector<bool>(N + 1, false);
	
	bool hasCycle = false;
	for (int u = 1; u <= N; u++) {
		if (dfscnt[u] == -1)
			dfs(u, hasCycle);
		if (hasCycle)
			break;
	}
		
	return hasCycle; 
}

void solve() {
	string answer = "";
	for (int i = 0; i < K; i++) {
		int u = query[i].first;
		int v = query[i].second;
		adj[u].push_back(v);
		if (getHasCycle()) {
			answer += '1';
			adj[u].pop_back();
			adj[v].push_back(u);
		} else
			answer += '0';
	}
	cout << answer << "\n";
	return;
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}

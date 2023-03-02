#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

#define INF 1000000001

typedef long long ll;

int N, M, K, dfscnt;
vector<vector<pair<int, int>>> adj;
vector<vector<vector<int>>> visited;
vector<vector<vector<bool>>> finished;
vector<vector<vector<int>>> cache;

void input() {
	// cout << "input" << endl;
	adj.clear();
	visited.clear();
	finished.clear();
	cache.clear();
	
	cin >> N >> M >> K;
	if (K == -1)
		K = 3;
	adj.resize(N + 1);
	for (int i = 0; i < N; i++) {
			int a, b;
			char c;
			cin >> a >> b >> c;
			adj[a].push_back({b, c - 'A'});
	}
	
	return;
}


void dfs(int u, int k, int prev_char, bool& isCycle) {
	// cout << u << " " << k << " " << prev_char << " " << dfscnt << " " << isCycle << endl;
	if (isCycle)
		return;
	visited[u][k][prev_char] = dfscnt++;
	
	for (pair<int, int> ele: adj[u]) {
		int v = ele.first;
		int next_char = ele.second;
		
		// cout << "adj " << v << " " << next_char << endl;
		
		int diff = next_char - prev_char;
		if (diff == -2 || diff == 1) {
			if (!visited[v][k][next_char])
				dfs(v, k, next_char, isCycle);
			else if (visited[v][k][next_char] < visited[u][k][prev_char] && !finished[v][k][next_char]) {
				isCycle = true;
				return;
			}
		}
		
		if (k == 1 || k == 2) {
			if (!visited[v][k - 1][prev_char])
				dfs(v, k - 1, prev_char, isCycle);
			else if (visited[v][k - 1][prev_char] < visited[u][k][prev_char] && !finished[v][k - 1][prev_char]) {
				isCycle = true;
				return;
			}
		} else if (k == 3) {
			if (!visited[v][k][prev_char])
				dfs(v, k, prev_char, isCycle);
			else if (visited[v][k][prev_char] < visited[u][k][prev_char] && !finished[v][k][prev_char]) {
				isCycle = true;
				return;
			}
		}
	}

	finished[u][k][prev_char] = true;
	return;
}


int dfs(int u, int k, int prev_char) {
	// cout << "dfs " << u << " " << k << " " << prev_char << endl;
	
	int& ret = cache[u][k][prev_char];
	if (ret != -1)
		return ret;
	
	ret = 0;
	for (pair<int, int> ele: adj[u]) {
		int v = ele.first;
		int next_char = ele.second;
		
		// cout << "adj " << v << " " << next_char << endl;
		
		int diff = next_char - prev_char;
		if (diff == -2 || diff == 1) {
			ret = max(ret, dfs(v, k, next_char) + 1);
		}
		
		if (k == 1 || k == 2) {
			ret = max(ret, dfs(v, k - 1, prev_char));
		} else if (k == 3) {
			ret = max(ret, dfs(v, k, prev_char));
		}
	}
	
	return ret;
}

void solve() {
	//cout << "solve" << endl;
	
	visited.clear();
	finished.clear();
	cache.clear();

	visited.resize(N + 1);
	finished.resize(N + 1);
	cache.resize(N + 1);
	for (int u = 1; u <= N; u++) {
		visited[u].resize(4);
		finished[u].resize(4);
		cache[u].resize(4);
		for (int k = 0; k < 4; k++) {
			visited[u][k].resize(4);
			finished[u][k].resize(4);
			cache[u][k].resize(4);
			for (int prev_char = 0; prev_char < 4; prev_char++)  {
				visited[u][k][prev_char] = 0;
				finished[u][k][prev_char] = false;
				cache[u][k][prev_char] = -1;
			}
		}
	}

	dfscnt = 1;
	bool isCycle = false;
	for (int u = 1; u <= N; u++) {
		for (pair<int, int> ele: adj[u]) {
			int v = ele.first;
			int prev_char = ele.second;
			if (!visited[v][K][prev_char])
				dfs(v, K, prev_char, isCycle);
		}
	}
	
	if (isCycle) {
		cout << "-1\n"; 
		return;
	}
	
	int ans = 0;
	for (int u = 1; u <= N; u++) {
		for (pair<int, int> ele: adj[u]) {
			int v = ele.first;
			int prev_char = ele.second;
			ans = max(ans, 1 + dfs(v, K, prev_char));
		}
	}
	
	cout << ans << "\n";

	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	ll T;
	cin >> T;
	
	for(ll t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}
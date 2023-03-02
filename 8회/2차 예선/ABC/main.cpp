#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 100001
typedef long long ll;

int N, M, K, dfscnt;

vector<vector<pair<int, int>>> adj;

int visited[MAXN][4][4];
bool finished[MAXN][4][4];
int cache[MAXN][4][4];

void input() {
	// cout << "input" << endl;
	adj.clear();
	cin >> N >> M >> K;
	if (K == -1)
		K = 3;
	adj.resize(N + 1);
	for (int i = 0; i < M; i++) {
			int a, b;
			char c;
			cin >> a >> b >> c;
			adj[a].push_back({b, c - 'A'});
	}
	
	for (int i = 1; i <= N; i++) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
	}
	
	return;
}


void dfs1(int u, int k, int prev_char, int dist, bool& isCycle) {
	// cout << u << " " << k << " " << prev_char << " " << dfscnt << " " << isCycle << endl;
	if (isCycle)
		return;
	visited[u][k][prev_char] = dist;
	
	for (pair<int, int> ele: adj[u]) {
		int v = ele.first;
		int next_char = ele.second;
		
		// cout << "adj " << v << " " << next_char << endl;
		
		int diff = next_char - prev_char;
		if (diff == -2 || diff == 1) {
			if (!visited[v][k][next_char])
				dfs1(v, k, next_char, dist + 1, isCycle);
			else if (visited[v][k][next_char] < dist && !finished[v][k][next_char]) {
				isCycle = true;
				return;
			}
		}
		
		if (k == 1 || k == 2) {
			if (!visited[v][k - 1][prev_char])
				dfs1(v, k - 1, prev_char, dist, isCycle);
			else if (visited[v][k - 1][prev_char] < dist && !finished[v][k - 1][prev_char]) {
				isCycle = true;
				return;
			}
		} else if (k == 3) {
			if (!visited[v][k][prev_char])
				dfs1(v, k, prev_char, dist, isCycle);
			else if (visited[v][k][prev_char] < dist && !finished[v][k][prev_char]) {
				isCycle = true;
				return;
			}
		}
	}

	finished[u][k][prev_char] = true;
	return;
}


int dfs2(int u, int k, int prev_char) {
	// cout << "dfs " << u << " " << k << " " << prev_char << endl;
	
	int& ret = cache[u][k][prev_char];
	if (ret != -1) {
		return ret;
	}
	
	ret = 0;
	for (pair<int, int> ele: adj[u]) {
		int v = ele.first;
		int next_char = ele.second;
		
		// cout << "adj " << v << " " << next_char << endl;
		
		int diff = next_char - prev_char;
		if (diff == -2 || diff == 1) {
			ret = max(ret, dfs2(v, k, next_char) + 1);
		}
		
		if (k == 1 || k == 2) {
			ret = max(ret, dfs2(v, k - 1, prev_char));
		} else if (k == 3) {
			ret = max(ret, dfs2(v, k, prev_char));
		}
	}
	
	return ret;
}

void solve() {
	//cout << "solve" << endl;
	memset(visited, 0, sizeof(visited));
	memset(finished, 0, sizeof(finished));
	memset(cache, -1, sizeof(cache));

	dfscnt = 1;
	bool isCycle = false;
	for (int u = 1; u <= N; u++) {
		for (pair<int, int> ele: adj[u]) {
			int v = ele.first;
			int prev_char = ele.second;
			if (!visited[v][K][prev_char])
				dfs1(v, K, prev_char, 1, isCycle);
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
			ans = max(ans, 1 + dfs2(v, K, prev_char));
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
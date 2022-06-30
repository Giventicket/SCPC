#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <algorithm>

#define INF 50000001

using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T, N, M;
	cin >> T;	
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		cin >> N >> M;
	
		vector<vector<tuple<int, int>>> adj = vector<vector<tuple<int, int>>>(N+1);
		
		// inputs		
		for(int i = 0; i < M; i++){
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
		}
		
		// outputs
	}
	
	return 0;
}
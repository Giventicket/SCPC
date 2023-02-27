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
	
		vector<vector<pair<int, int>>> adj = vector<vector<pair<int, int>>>(N+1);
		
		// inputs		
		for(int i = 0; i < M; i++){
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
		}
		
		// outputs
		set<int> intermediate;
		
		for(int v = 1; v <= N; v++){
			vector<int> dist = vector<int>(N+1, INF);
			dist[v] = 0;
			priority_queue<tuple<int, int, int, int>> pq;
			pq.push(make_tuple(0, 1, v, -1));
			while(!pq.empty()){
				tuple<int, int, int, int> ele = pq.top();
				pq.pop();
				int curDist = -get<0>(ele);
				int vertexCnt = get<1>(ele);
				int cur = get<2>(ele);
				int parent = get<3>(ele);
				
				if(dist[cur] < curDist)
					continue;
				
				if(vertexCnt >= 3)
					intermediate.insert(parent);
				
				for(pair<int, int> ele: adj[cur]){
					int u = ele.first;
					int weight = ele.second;
					if(dist[u] >= curDist + weight){
						dist[u] = curDist + weight;
						pq.push(make_tuple(-dist[u], vertexCnt + 1, u, cur));
					}
				}
			}
		}
		
		vector<int> answer;
		for(int i=1; i <= N; i++){
			if(intermediate.find(i) == intermediate.end())
				answer.push_back(i);
		}
		cout << answer.size() << " ";
		for(int ele: answer)
			cout << ele << " ";
		cout << "\n";
	}
	
	return 0;
}
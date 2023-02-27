#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <algorithm>

#define INF 50000001

using namespace std;

int N, M;
vector<vector<tuple<int, int>>> adj;
vector<int> cnt;
set<int> answer;

void countShortestPath(int source){
	cnt = vector<int>(N+1, 0);
	priority_queue<tuple<int, int>> pq;
	vector<int> dist = vector<int>(N+1, INF);
	dist[source] = 0;
	pq.push({-dist[source], source});
	while(!pq.empty()){
		int curW = -get<0>(pq.top());
		int cur = get<1>(pq.top());
		pq.pop();
		if(dist[cur] < curW)
			continue;
		cnt[cur]++;
		for(tuple<int, int> ele: adj[cur]){
			int next = get<0>(ele);
			int weight = get<1>(ele);
			if(dist[next] >= curW + weight){
				dist[next] = curW + weight;
				pq.push({-dist[next], next});
			}
		}
	}
	return;
}

void renewAnswer(int source){
	countShortestPath(source);
	priority_queue<tuple<int, int, int>> pq;
	vector<int> dist = vector<int>(N+1, INF);
	dist[source] = 0;
	pq.push({-dist[source], source, -1});
	while(!pq.empty()){
		int curW = -get<0>(pq.top());
		int cur = get<1>(pq.top());
		int parent = get<2>(pq.top());
		pq.pop();
		if(dist[cur] < curW)
			continue;
		if(cur != source && parent != source && cnt[cur] == 1)
			answer.insert(parent);
		for(tuple<int, int> ele: adj[cur]){
			int next = get<0>(ele);
			int weight = get<1>(ele);
			if(dist[next] >= curW + weight){
				dist[next] = curW + weight;
				pq.push({-dist[next], next, cur});
			}
		}
	}
	return;
}

int main(){
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;	
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		cin >> N >> M;
	
		// inputs		
		answer.clear();
		adj = vector<vector<tuple<int, int>>>(N+1);
		
		for(int i = 0; i < M; i++){
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
		}
		
		// outputs
		for(int source = 1; source <= N; source++)
			renewAnswer(source);
		
		cout << answer.size() << " ";
		for(int ele: answer)
			cout << ele << " ";
		cout << "\n";		
	}
	
	return 0;
}
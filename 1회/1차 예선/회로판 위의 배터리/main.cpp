#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;

bool isOverlapping(pair<int, int>& p1, pair<int, int>& p2, double z){
	double dist = max(abs(p1.first - p2.first), abs(p1.second - p2.second));
	if(4 * z * z >= dist * dist)
		return true;
	return false;
}

vector<vector<int>> makeGraph(vector<pair<pair<int, int>, pair<int, int>>>& vt, double z){
	graph = vector<vector<int>>(vt.size() * 2);
	
	for(int i = 0; i < vt.size(); i++){
		for(int j = i + 1; j < vt.size(); j++){
			pair<pair<int, int>, pair<int, int>>& line1 = vt[i];
			pair<pair<int, int>, pair<int, int>>& line2 = vt[j];
			if(isOverlapping(line1.first, line2.first, z)){
				graph[i * 2].push_back(j * 2);
				graph[j * 2].push_back(i * 2);
			}
			if(isOverlapping(line1.first, line2.second, z)){
				graph[i * 2].push_back(j * 2 + 1);
				graph[j * 2 + 1].push_back(i * 2);
			}
			if(isOverlapping(line1.second, line2.first, z)){
				graph[i * 2 + 1].push_back(j * 2);
				graph[j * 2].push_back(i * 2 + 1);
			}
			if(isOverlapping(line1.second, line2.second, z)){
				graph[i * 2 + 1].push_back(j * 2 + 1);
				graph[j * 2 + 1].push_back(i * 2 + 1);
			}
		}
	}
	
	return graph;
}

bool isComplete(vector<vector<int>>& graph){
	vector<bool> vertexColor = vector<bool>(graph.size(), true);
	
	// vertex coloring
	while(true){
		bool changed = false;
				
		for(int i = 0; i < graph.size() / 2; i++){		
			set<int> st1, st2;
			
			if(vertexColor[i * 2]){
				for(int u : graph[i * 2])
					if(vertexColor[u])
						st1.insert(u / 2);
				if(st1.size() != (graph.size() / 2 - 1)){
					vertexColor[i * 2] = false;
					changed = true;
				}
			}
			
			if(vertexColor[i * 2 + 1]){
				for(int u : graph[i * 2 + 1])
					if(vertexColor[u])
						st2.insert(u / 2);
				if(st2.size() != (graph.size() / 2 - 1)){
					vertexColor[i * 2 + 1] = false;
					changed = true;
				}
			}
		}	

		if(!changed)
			break;
	}
	
	//check black vertice
	for(int i = 0; i < graph.size() / 2; i++){		
		if(vertexColor[i * 2] || vertexColor[i * 2 + 1])
			continue;
		else
			return false;
	}
	return true;
}

int main(){
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T, N;
	cin >> T;	
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		cin >> N;
		
		vector<pair<pair<int, int>, pair<int, int>>> vt; // element -> line
		
		// inputs		
		for(int i = 0; i < N; i++){
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			vt.push_back({{a, b}, {c, d}});
		}
		
		// outputs
		double lo = 0;
		double hi = 100000000;
		for(int iter = 0; iter < 100; iter++){
			double mid = (lo + hi) / 2;
			vector<vector<int>> graph = makeGraph(vt, mid);
			
			if(isComplete(graph)){
				hi = mid;
			} else{
				lo = mid;
			}
		}
		cout << lo << "\n";
	}
	
	return 0;
}
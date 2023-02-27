#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

using namespace std;

int main(){
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	//lookup table
	map<pair<int, int>, int> m; //거울종류, dir
	m[{1, 0}] = 1;
	m[{1, 1}] = 0;
	m[{1, 2}] = 3;
	m[{1, 3}] = 2;
	m[{2, 0}] = 3;
	m[{2, 1}] = 2;
	m[{2, 2}] = 1;
	m[{2, 3}] = 0;
	
	int T, N;
	cin >> T;	
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		cin >> N;
		
		vector<vector<int>> vt = vector<vector<int>>(N, vector<int>(N, 0));
		set<int> st;
		
		// inputs		
		for(int i=0; i < N; i++){
			string str;
			cin >> str;
			for(int j=0; j < N; j++){
				vt[i][j] = str.at(j) - '0';
			}
		}
		
		// outputs
		int dir = 0;
		int x = 0, y = 0;
		
		while(x >= 0 && x < N && y >= 0 && y < N){
			if(vt[x][y]){
				st.insert(N * x + y);
				dir = m[{vt[x][y], dir}];				
			}
			switch(dir){
				case 0:
				y++;
				break;
				case 1:
				x--;
				break;
				case 2:
				y--;
				break;
				case 3:
				x++;
				break;
				default:
				break;
			}
		}
		cout << st.size() << "\n";
	}
	
	return 0;
}

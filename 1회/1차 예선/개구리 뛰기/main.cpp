#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	vector<int> vt;
	
	int T, N, K, temp;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		// inputs
		cout << "Case #" << t << "\n";
		vt.clear();
		vt.push_back(0);
		cin >> N;
		for(int n=0; n < N; n++){
			cin >> temp;
			vt.push_back(temp);
		}
		cin >> K;
		// outputs
		int i = 0, count = 0;
		while(i != N){
			int j = upper_bound(vt.begin(), vt.end(), vt[i] + K) - vt.begin();
			j--;
			if(i == j){
				count = -1;
				break;
			}
			i = j;
			count++;
		}
		cout << count << "\n";
	}
	
	return 0;
}

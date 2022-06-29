#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <cstring>

#define MINA -10000001
#define MAXB 10000001

using namespace std;

int N;
vector<tuple<int, int>> segVt;
vector<int> vt;

int getMaxCnt(){
	for(tuple<int, int>& ele: segVt){
		int a = get<0>(ele);
		int b = -get<1>(ele);
		if(vt.size() == 0){
			vt.push_back(-b);
		} else if(-b >= vt[vt.size() - 1]){
			vt.push_back(-b);
		} else{
			auto it = upper_bound(vt.begin(), vt.end(), -b);
			*it = -b;
		}		
	}
	return vt.size() - 1;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;	
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		cin >> N;
		
		// inputs
		vt.clear();
		segVt.clear();
		for(int i = 0; i < N; i++){
			int a, b;
			cin >> a >> b;
			segVt.push_back(make_tuple(a, -b));
		}
		segVt.push_back({MINA, -MAXB});
		sort(segVt.begin(), segVt.end());		
		
		// outputs
		cout << getMaxCnt() << endl;		
	}
	
	return 0;
}

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T, a, b, c;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		// inputs
		cout << "Case #" << t << "\n";
		cin >> a >> b >> c;
		
		// outputs
		for(int iter = 0; iter < c; iter++){
			int N, K;
			cin >> N >> K;
			vector<tuple<bool, int, int, bool>> vt; // team, range num1, range num2, bool value(canWin?)
			vt.push_back(make_tuple(0, N - a + 1, N, false));
			vt.push_back(make_tuple(1, N - b + 1, N, false));
			while(!vt.empty()){
				tuple<bool, int, int, bool> ele = vt.back();
				vt.pop_back();
				bool team = get<0>(ele);
				int s1 = get<1>(ele);
				int s2 = get<2>(ele);
				bool canWin = get<3>(ele);
				
				if(s2 <= 0)
					continue;
				
				if(team == 0 && s1 <= 1 && 1 <= s2){
					cout << (canWin ? "a" : "b");
					break;
				}
				
				if(canWin){
					int value = team * a + !team * b;
					if(s1 - value <= s2 - K * value)
						vt.push_back(make_tuple(!team, s1 - value, s2 - K * value, !canWin));
				} else{
					int value = team * a + !team * b;
					if(s1 - K * value <= s2 - value)
						vt.push_back(make_tuple(!team, s1 - K * value, s2 - value, !canWin));
				}
			}
		}	
		cout << "\n";		
	}
	
	return 0;
}

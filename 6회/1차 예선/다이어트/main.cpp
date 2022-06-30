#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T, N, K;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		// inputs
		cout << "Case #" << t << "\n";
		cin >> N >> K;
		vector<int> A = vector<int>(N);
		vector<int> B = vector<int>(N);
		for(int i = 0; i < N; i++)
			cin >> A[i];
		for(int i = 0; i < N; i++)
			cin >> B[i];
		
		// outputs
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		
		set<int> C;
		for(int i = 0; i < K; i++)
			C.insert(A[i] + B[K-1-i]);
		auto it = C.end();
		it--;
		cout << *it << "\n";
	}
	
	return 0;
}

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int n, t;
vector<int> A, B;
set<int> should_be_zero; // indice set of A that should be zero
set<int> ones_B; // indice set of B that are one
set<int> ones_A; // indice set of A that should be one satisfying the conditions of problem
vector<vector<int>> A_to_B, B_to_A;

void input() {
	string str; 
	cin >> n >> t >> str;
	
	A.clear();
	B.clear();
	A_to_B.clear();
	B_to_A.clear();
	should_be_zero.clear();
	ones_B.clear();
	ones_A.clear();

	A.resize(n + 1);
	B.resize(n + 1);
	A_to_B.resize(n + 1);
	B_to_A.resize(n + 1);
	
	
	for (int i = 1; i <= n; i++)
		B[i] = str[i - 1] - '0';
		
	
	for (int i = 1; i <= n; i++) {
		if (B[i] == 0) {
			if (i + t <= n) 
				should_be_zero.insert(i + t);
			if (i - t >= 1)
				should_be_zero.insert(i - t);
		} else
			ones_B.insert(i);
	}

	
	for (int i = 1; i <= n; i++) {
		if (i + t <= n && B[i] == 1) {
			A_to_B[i + t].push_back(i);
			B_to_A[i].push_back(i + t);
		}
		
		if (i - t >= 1 && B[i] == 1) {
			A_to_B[i - t].push_back(i);
			B_to_A[i].push_back(i - t);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		sort(A_to_B[i].rbegin(), A_to_B[i].rend());
		sort(B_to_A[i].rbegin(), B_to_A[i].rend());
	}
	
	return;
}

void solve() {
	set<int>::iterator it;
	for (it = should_be_zero.begin(); it != should_be_zero.end(); it++) {
		int a_idx = (*it);
		for (int b_idx: A_to_B[a_idx]) {
			if (!B[b_idx])
				continue;
			for (int aa_idx: B_to_A[b_idx]) {
				if (aa_idx == a_idx || should_be_zero.count(aa_idx) != 0)
					continue;
				if (ones_B.count(b_idx) != 0) {
					ones_B.erase(b_idx);
					ones_A.insert(aa_idx);
					//cout << aa_idx << " " << b_idx << endl;
					for (int bb_idx: A_to_B[aa_idx]) {
						if (bb_idx == b_idx || !B[bb_idx])
							continue;
						if (ones_B.count(bb_idx) != 0) {
							ones_B.erase(bb_idx);
							//cout << aa_idx << " " << bb_idx << endl;
						}
					}
				}
				
			}
		}
	}
	
	while (ones_B.size() > 0) {
		it = ones_B.begin();
		int b_idx = (*it);
		for (int a_idx: B_to_A[b_idx]) {
			if (should_be_zero.count(a_idx) != 0)
				continue;
			if (ones_B.count(b_idx) != 0) {
				ones_B.erase(b_idx);
				ones_A.insert(a_idx);
				//cout << a_idx << " " << b_idx << endl;	
				for (int bb_idx: A_to_B[a_idx]) {
					if (bb_idx == b_idx || !B[bb_idx])
						continue;
					if (ones_B.count(bb_idx) != 0) {
						ones_B.erase(bb_idx);
						//cout << a_idx << " " << bb_idx << endl;
					}
				}
			}
		}
	}
	
	for (it = ones_A.begin(); it != ones_A.end(); it++)
		A[(*it)] = 1;
	for (int i = 1; i <= n; i++)
		if(A[i])
			cout << A[i];
		else
			cout << '0';
	cout << "\n";
	return;
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
		input();
		solve();
	}
	
	return 0;
}

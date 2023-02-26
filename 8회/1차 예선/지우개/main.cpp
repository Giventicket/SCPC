#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

int N, M;
string X, Y;

vector<int> A_X, B_X;
vector<int> A_Y, B_Y;

void input() {
	// cout << "input" << endl;
	A_X.clear(); 
	B_X.clear();
	A_Y.clear(); 
	B_Y.clear();

	cin >> N >> M;
	cin >> X >> Y;
	
	for (int i = 0; i < N; i++) {
		if (X[i] == 'a')
			A_X.push_back(i);
		else
			B_X.push_back(i);
	}
	
	for (int i = 0; i < M; i++) {
		if (Y[i] == 'a')
			A_Y.push_back(i);
		else
			B_Y.push_back(i);
	}
	
	return;
}

vector<int> get_partial_match(vector<int>& S) {
	// cout << "get_partial_match" << endl;
	vector<int> pi(S.size());
	int begin = 1;
	int matched = 1;
	while (begin + matched < S.size()) {
		while (matched < S.size() && S[begin + matched] - S[begin + matched - 1] == S[matched] - S[matched - 1]) {
			pi[begin + matched] = matched;
			matched++; 
		}
		if (matched == 1)
			begin++;
		else {
			matched = pi[matched];
			begin += matched;
		}			
	}
	return pi;
}

vector<int> kmp(vector<int>& P, vector<int>& S) {
	// cout << "kmp" << endl;
	vector<int> vt;
	vector<int> pi = get_partial_match(S);
	
	int begin = 0;
	int matched = 1;
	while (begin + matched <= P.size() - S.size() + 1) {
		while (matched < S.size() && P[begin + matched] - P[begin + matched - 1] == S[matched] - S[matched - 1])
			matched++; 

		if (matched == S.size())
			vt.push_back(begin);

		if (matched == 1)
			begin++;
		else {
			matched = pi[matched];
			begin += matched + 1;
		}			
	}
	
	for (int ele: P)
		cout << ele << " ";
	cout << endl;
	for (int ele: S)
		cout << ele << " ";
	cout << endl;
	for (int ele: vt)
		cout << ele << " ";
	cout << endl;

	return vt;
}

void solve() {
	// cout << "solve" << endl;
	vector<int> A_candidates = kmp(A_X, A_Y);
	vector<int> B_candidates = kmp(B_X, B_Y);
	
	for (int ele : A_candidates)
		cout << ele << " ";
	cout << endl;
	for (int ele : B_candidates)
		cout << ele << " ";
	cout << endl;
	
	set<int> _B_candidates;
	for (int ele: B_candidates)
		_B_candidates.insert(ele);
	
	for (int A_idx: A_candidates) {
		int B_idx = A_idx - (A_Y[0] - B_Y[0]);
		if (_B_candidates.find(B_idx) != _B_candidates.end()) {
				cout << "YES" << "\n";
				return;
		}
	}
	cout << "NO" << "\n";
	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	ll T;
	cin >> T;
	
	for(ll t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}

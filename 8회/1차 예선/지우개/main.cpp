#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

int N, M, a_count, b_count;
string X, Y;

vector<int> A_X, B_X;
vector<int> A_Y, B_Y;
map<int, int> B_X_inverse;

void input() {
	// cout << "input" << endl;
	A_X.clear(); 
	B_X.clear();
	A_Y.clear(); 
	B_Y.clear();
	a_count = b_count = 0;

	cin >> N >> M;
	cin >> X >> Y;
	
	if (Y[0] == 'b') {
		for (int i = 0; i < N; i++) {
			if (X[i] == 'a')
				X[i] = 'b';
			else
				X[i] = 'a';
		}
		
		for (int i = 0; i < M; i++) {
			if (Y[i] == 'a')
				Y[i] = 'b';
			else
				Y[i] = 'a';
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (X[i] == 'a')
			A_X.push_back(i);
		else
			B_X.push_back(i);
	}
	
	for (int i = 0; i < M; i++) {
		if (Y[i] == 'a') {
			A_Y.push_back(i);
			a_count++;
		} else {
			B_Y.push_back(i);
			b_count++;
		}
	}
	
	B_X_inverse.clear();
	for (int i = 0; i < (int) B_X.size(); i++)
		B_X_inverse[B_X[i]] = i;
	return;
}

bool cmp(int a_start, int b_start) {
	int a_end = a_start + a_count;
	int b_end = b_start + b_count;
	if (a_end > (int) A_X.size() || b_end > (int) B_X.size())
		return false;
	
	// cout << a_start << " " << a_end << " " << b_start << " " << b_end << "\n";
	// cout << A_X[a_start] << " " << A_X[a_end - 1] << " " << B_X[b_start] << " " << B_X[b_end - 1] << "\n";
	
	vector<int> vt;
	for (int i = a_start; i < a_end; i++)
		vt.push_back(A_X[i]);
	for (int i = b_start; i < b_end; i++)
		vt.push_back(B_X[i]);
	sort(vt.begin(), vt.end());
	
	for (int i = 0; i < (int) vt.size(); i++) {
		if (X[vt[i]] != Y[i])
			return false;
	}
	return true;	
}

void solve() {
	bool b_appeared = false;
	bool a_appeared = false;
	int first_As = 0;
	int first_Bs = 0;
	for (int i = 0; i < Y.size(); i++) {
		if (!b_appeared && Y[i] == 'b') {
			first_Bs++;
			b_appeared = true;
		} else if (b_appeared && Y[i] == 'b') 
			first_Bs++;
		else if (b_appeared && Y[i] == 'a') {
			a_appeared = true;
			break;
		} else 
			first_As++;
	}
	
	if (!first_Bs) {
		if ((int) A_X.size() > (int) Y.size())
			cout << "YES\n";
		else
			cout << "NO\n";
		return;
	} else if (!a_appeared) {
		vector<pair<int, int>> A_pair, B_pair;
		
		for (int a_start = 0; a_start < (int) A_X.size(); a_start++) {
			if (a_start + first_As < (int) A_X.size())
				A_pair.push_back({a_start, a_start + first_As});
		}
		
		for (int b_start = 0; b_start < (int) B_X.size(); b_start++) {
			if (b_start + first_Bs < (int) B_X.size())
				B_pair.push_back({b_start, b_start + first_Bs});
		}
		
		for (pair<int, int> a_p: A_pair) {
			for (pair<int, int> b_p: B_pair) {
				if (a_p.second < b_p.first) {
					cout << "YES\n";
					return;
				}
			}
		}
		
		cout << "NO\n";
		return;
	}
	
	// cout << "first " << first_As << " " << first_Bs << endl;
	for (int a_start = 0; a_start + first_As < (int) A_X.size(); a_start++) {
		int B_idx = A_X[a_start + first_As] - first_Bs;
		if (B_X_inverse.find(B_idx) == B_X_inverse.end())
			continue;
		int b_start = B_X_inverse[B_idx]; //deterministic
		if (cmp(a_start, b_start)){
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
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
		if (N > 2000)
		    continue;
		solve();
	}
	
	return 0;
}

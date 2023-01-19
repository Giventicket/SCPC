#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int ll;

ll N, K;
string S;
vector<string> Ps;
vector<int> alphabet_to_pos, prev_S, prev_P;


void input() {
	cin >> N >> K;
	cin >> S;
	Ps.clear();
	Ps.resize(K);
	for(int i = 0; i < K; i++)
		cin >> Ps[i];
	return;
}

void renew_prev_S() {
	int n = S.size();
	prev_S.clear();
	prev_S = vector<int>(n, -1);
	alphabet_to_pos.clear();
	alphabet_to_pos = vector<int>( 26, -1);
	for(int i = 0; i < n; i++) {
		int cur = S[i] - 'a';
		if (alphabet_to_pos[cur] != -1)
			prev_S[i] = i - alphabet_to_pos[cur]; // distance from p[i]: smallest value of i - j if p[i] == p[j] and j is in [0, i - 1]. 
		alphabet_to_pos[cur] = i;
	}
	return;
}

void renew_prev_P(string& P) {
	int m = P.size();
	prev_P.clear();
	prev_P = vector<int>(m, -1);
	alphabet_to_pos.clear();
	alphabet_to_pos = vector<int>(26, -1);
	for(int i = 0; i < m; i++) {
		int cur = P[i] - 'a';
		if (alphabet_to_pos[cur] != -1)
			prev_P[i] = i - alphabet_to_pos[cur]; // distance from p[i]: smallest value of i - j if p[i] == p[j] and j is in [0, i - 1]. 
		alphabet_to_pos[cur] = i;
	}
	return;
}


vector<int> get_fail(string& P) {
	int m = P.size();
	vector<int> fail(m, 0);
	int j = 0;
	for (int i = 1; i < m; i++) {
		while(j > 0 && !((prev_P[i] == prev_P[j]) || ((prev_P[j] == -1) && prev_P[i] > j)))
			j = fail[j - 1];
		if ((prev_P[i] == prev_P[j]) || ((prev_P[j] == -1) && prev_P[i] > j))
			fail[i] = ++j;
	}
	return fail;
}

ll kmp(string& P) {
	//cout << P << endl;
	int n = S.size();
	int m = P.size();
	ll cnt = 0;
	vector<int> fail = get_fail(P);
	
	/*
	cout << "prev_P ";
	for (int ele: prev_P)
		cout << ele << " ";
	cout << endl;

	cout << "fail ";
	for (int ele: fail)
		cout << ele << " ";
	cout << endl;
	*/
	
	int j = 0;
	for (int i = 0; i < n; i++) {
		while(j > 0 && !((prev_S[i] == prev_P[j]) || ((prev_P[j] == -1) && prev_S[i] > j))) {
			j = fail[j - 1];
		}
			
		if ((prev_S[i] == prev_P[j]) || ((prev_P[j] == -1) && prev_S[i] > j)) {
			if (j == m - 1) {
				cnt++;
				j = fail[j];
			} else
				j++;
		}
	}
	return cnt;
}
 
void solve() {
	renew_prev_S();
	ll ans = 0;
	for(ll i = 1; i <= K; i++) {
		renew_prev_P(Ps[i - 1]);
		ans += i * kmp(Ps[i - 1]);
	}
	cout << ans << "\n";
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

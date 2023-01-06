#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define lli long long int

int n, m, l, cnt_odds;
vector<vector<lli>> S;


void input() {
	cin >> n >> m;
	S.clear();
	
	S.resize(n);
	
	cnt_odds = 0;
	for (int i = 0; i < n; i++) {
		cin >> l;
		cnt_odds += (l % 2);
		S[i].resize(l);
		for (int j = 0; j < l; j++)
			cin >> S[i][j];
		sort(S[i].begin(), S[i].end());
	}
	return;
}

lli get_value0 () { // cnt_odds가 2가 아닌 경우
	lli ans = 0;
	vector<lli> can_be_end;
	for (int i = 0; i < n; i++) {
		if (S[i].size() % 2) {
			ans += S[i][0] * 2 + S[i][1];
			ans += S[i][2] + S[i][3];
		} else {
			ans += S[i][0] + S[i][1];
			ans += S[i][2] + S[i][3];
		}
		can_be_end.push_back(S[i][2] + S[i][3]);
	}
	sort(can_be_end.rbegin(), can_be_end.rend());
	return ans - can_be_end[0] - can_be_end[1];
}

lli get_value1 () { // cnt_odds가 2이고 양끝이 홀수인 경우
	lli ans = 0;
	for (int i = 0; i < n; i++) {
		if (S[i].size() % 2) {
			ans += S[i][0] * 2 + S[i][1];
		} else {
			ans += S[i][0] * 2 + S[i][2];
			ans += S[i][1] * 2 + S[i][3];
		}
	}	
	return ans;
}

lli get_value2 () { // cnt_odds가 2이고 양끝이 홀수가 아닌 경우
	lli ans = 0;
	vector<lli> tmp;
	vector<lli> can_be_end;
	for (int i = 0; i < n; i++) {
		if (S[i].size() % 2) {
			ans += S[i][0] * 2 + S[i][1];
			ans += S[i][2] + S[i][3];
			tmp.push_back(S[i][2] + S[i][3]);
		} else {
			ans += S[i][0] + S[i][1];
			ans += S[i][2] + S[i][3];
			can_be_end.push_back(S[i][2] + S[i][3]);
		}
	}
	sort(tmp.rbegin(), tmp.rend());
	can_be_end.push_back(tmp[0]);
	sort(can_be_end.rbegin(), can_be_end.rend());
	return ans - can_be_end[0] - can_be_end[1];		
}

void solve() {	
	if (n >= 3 && cnt_odds == 2) {
		cout << min(get_value1(), get_value2()) << "\n";
	} else {
		cout << get_value0() << "\n";
	}
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

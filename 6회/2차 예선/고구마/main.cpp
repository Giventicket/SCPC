#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int N;
long long int M;
vector<long long int> price;

void input() {
	cin >> N >> M;
	price.clear();
	price.resize(N);
	for (int i = 0; i < N; i++)
		cin >> price[i];
	return;
}

long long int solve(){
	long long int answer = 0;
	set<long long int> st;
	long long int currentSum = 0;
	st.insert(0);
	for(int i = 0; i < N; i++) {
		currentSum += price[i];
		st.insert(currentSum);
		set<long long int>::iterator it = st.lower_bound(currentSum - M);
		answer = max(answer, currentSum - (*it));
	}
	return answer;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for (int t = 1; t <= T; t++) {
		// inputs
		cout << "Case #" << t << "\n";
		input();
		cout << solve() << "\n";
	}
	
	return 0;
}

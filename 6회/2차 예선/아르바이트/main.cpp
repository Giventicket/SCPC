#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define MAX 20000001

int n, K, Q;
vector<int> price;
vector<pair<int, int>> change;
vector<int> partial_sum;
int tree[MAX];

void input() {
	memset(tree, 0, sizeof(tree));
	cin >> n >> K >> Q;
	price.clear();
	price.resize(n + 1);
	change.clear();
	change.resize(Q + 1);
	for (int i = 1; i <= n; i++)
		cin >> price[i];
	for (int i = 1; i <= Q; i++)
		cin >> change[i].first >> change[i].second;
	return;
}

void update(int index, int delta) {
	while(index <= MAX - 1) {
		tree[index] += delta;
		index += (index & (-index));
	}
	return;
}

int sum(int index) {
	int ans = 0;
	while(index > 0) {
		ans += tree[index];
		index -= (index & (-index));
	}
	return ans;
}

int median() {
	int left = 1;
	int right = MAX - 1;
	int median_pos = (n - K + 1) / 2 + 1;
	
	while(left < right) {
		int mid = (left + right) / 2;
		int mSum = sum(mid);
		if (mSum < median_pos)
			left = mid + 1;
		else
			right = mid;
	}
	
	return right;
}

void solve(){
	// compute partial_sum
	partial_sum.clear();
	partial_sum.resize(n - K + 2);
	for(int i = 1; i < partial_sum.size(); i++) {
		partial_sum[i] = 0;
		for(int j = 0; j < K; j++)
			partial_sum[i] += price[i + j];
	}
	
	// make Fenwick tree
	for(int i = 1; i < partial_sum.size(); i++)
		update(partial_sum[i], 1);
	
	// median without changes
	vector<int> answer;
	answer.push_back(median());
	
	// median with changes
	for(int i = 1; i <= Q; i++) {
		pair<int, int> ele = change[i];
		int idx = ele.first;
		int val = ele.second;
		
		int s = max(1, idx - K + 1);
		int e = min(n - K + 1, idx);
				
		for (int i = s; i <= e; i++) {
			update(partial_sum[i], -1);
			partial_sum[i] += (val - price[idx]);
			update(partial_sum[i], 1);
		}
		price[idx] = val;
		answer.push_back(median());
	}
	
	for (int ele: answer)
		cout << ele << " ";
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
	
	
	for (int t = 1; t <= T; t++) {
		// inputs
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}

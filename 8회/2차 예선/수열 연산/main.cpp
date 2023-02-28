#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1000000001

typedef long long ll;

struct RMQ {
	vector<int> seg;
	vector<int> lazy;
	int sz;
	
	RMQ(vector<int>& arr) {
		// cout << "RMQ" << endl;
		sz = (int) arr.size();
		seg.resize(sz * 4);
		lazy.resize(sz * 4);
		init(1, 0, sz - 1, arr);
	}
	
	void init(int node, int nodeLeft, int nodeRight, vector<int>& arr) {
		// cout << "init node" << endl;
		if (nodeLeft == nodeRight) {
			seg[node] = arr[nodeLeft];		
			return;
		}
		int nodeMid = (nodeLeft + nodeRight) / 2;
		init(node * 2, nodeLeft, nodeMid, arr);
		init(node * 2 + 1, nodeMid + 1, nodeRight, arr);
		seg[node] = max(seg[node * 2], seg[node * 2 + 1]);
		return;
	}
	
	void propagate(int node, int nodeLeft, int nodeRight) {
		// cout << "propagate" << endl;
		if (lazy[node]) {
			if (nodeLeft != nodeRight) {
				seg[2 * node] += lazy[node];	
				seg[2 * node + 1] += lazy[node];
				lazy[2 * node] += lazy[node];	
				lazy[2 * node + 1] += lazy[node];				
			}
			lazy[node] = 0;
		}
		return;
	}
	
	int query(int left, int right) {
		// cout << "query" << endl;
		return query(1, 0, sz - 1, left, right);
	}
	
	int query(int node, int nodeLeft, int nodeRight, int left, int right) {
		// cout << "query node" << endl;
		propagate(node, nodeLeft, nodeRight);
		if (nodeLeft > right || nodeRight < left)
			return -INF;
		if (left <= nodeLeft &&  nodeRight <= right)
			return seg[node];
		
		int nodeMid = (nodeLeft + nodeRight) / 2;
		int lVal = query(node * 2, nodeLeft, nodeMid, left, right);
		int rVal = query(node * 2 + 1, nodeMid + 1, nodeRight, left, right);
		return seg[node] = max(lVal, rVal);
	}
	
	void update(int left, int right, int val) {
		// cout << "update" << endl;
		update(1, 0, sz - 1, left, right, val);	
		return;
	}
	
	int update(int node, int nodeLeft, int nodeRight, int left, int right, int val) {
		// cout << "update node" << endl;
		propagate(node, nodeLeft, nodeRight);
		if (left <= nodeLeft &&  nodeRight <= right) {
			seg[node] += val;
			lazy[node] += val;
			return seg[node];
		}
		if (nodeLeft > right || nodeRight < left)
			return -INF;
		int nodeMid = (nodeLeft + nodeRight) / 2;
		int lVal = update(node * 2, nodeLeft, nodeMid, left, right, val);
		int rVal = update(node * 2 + 1, nodeMid + 1, nodeRight, left, right, val);
		return seg[node] = max(lVal, rVal);
	}
};

int N, k;
vector<int> arr;

void input() {
	// cout << "input" << endl;
	
	arr.clear();
	
	cin >> N >> k;
	arr.resize(N);
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	for (int i = 0; i < N; i++) {
		arr[i] -= k;
		if (arr[i] > 0)
			arr[i] = 0;
		else
			arr[i] = -arr[i];
	}

	return;
}

void solve() {
	// cout << "solve" << endl;
	
	int left = 0;
	int right = N - 1;
	RMQ rmq(arr);
	ll ans = 0;
	int op_count = 0;
	
	while (left <= right) {
		int lVal = rmq.query(left, left);
		int rVal = rmq.query(right, right);
		// cout << lVal << " " << rVal << endl;
		if (lVal <= 0)
			left++;
		else if (rVal <= 0)
			right--;
		else {
			int val = min(rVal, lVal);
			rmq.update(left, right, -val);
			// cout << "ops " << left << " " << right << " " << val << endl;
			op_count += val;
			/*
			for (int i = 0; i < N; i++) {
				cout << rmq.query(i, i) << " ";
			}
			cout << "\n";
			*/
			ans += (ll) (right - left + 1) * (ll) val;
		}
	}
	cout << op_count << " " << ans << "\n";
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
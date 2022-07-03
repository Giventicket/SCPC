#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

//range maximum query(segment tree with lazy propagation)
struct RMQ{
	int sz = -1;
	vector<int>& arr;
	vector<int> seg; // maxValue, argmax
	vector<int> lazy;
	
	RMQ(vector<int>& arr): arr(arr){
		sz = arr.size();
		seg = vector<int>(sz * 4);
		lazy = vector<int>(sz * 4);
		init(0, sz - 1, 1);
		arr.clear();
	}
	
	int merge(int& lValue, int& rValue){
		return max(lValue, rValue);
	}
	
	int init(int nodeLeft, int nodeRight, int node){
		if(nodeLeft == nodeRight)
			return seg[node] = arr[nodeLeft];
		int nodeMid = (nodeLeft + nodeRight) / 2;
		int lValue = init(nodeLeft, nodeMid, node * 2);
		int rValue = init(nodeMid + 1, nodeRight, node * 2 + 1);
		return seg[node] = merge(lValue, rValue);
		
	}
	
	void propagate(int nodeLeft, int nodeRight, int node){
		seg[node] += lazy[node];
		if(nodeLeft != nodeRight){
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;	
		return;		
	}
	
	int query(int left, int right, int nodeLeft, int nodeRight, int node){
		propagate(nodeLeft, nodeRight, node);
		if(right < nodeLeft || nodeRight < left)
			return 0; // cannot affect
		if(left <= nodeLeft && nodeRight <= right)
			return seg[node];
		int nodeMid = (nodeLeft + nodeRight) / 2;
		int lValue = query(left, right, nodeLeft, nodeMid, node * 2);
		int rValue = query(left, right, nodeMid + 1, nodeRight, node * 2 + 1);
		return merge(lValue, rValue);
	}
	
	int query(int left, int right){
		return query(left, right, 0, sz - 1, 1);
	}
	
	int query(){
		return query(0, sz - 1);
	}
	
	int update(int left, int right, int nodeLeft, int nodeRight, int node, int value){
		propagate(nodeLeft, nodeRight, node);
		if(right < nodeLeft || nodeRight < left)
			return seg[node];
		if(left <= nodeLeft && nodeRight <= right){
			if(nodeLeft != nodeRight){
				lazy[node * 2] += value;
				lazy[node * 2 + 1] += value;
			}
			return seg[node] += value;
		}			
		int nodeMid = (nodeLeft + nodeRight) / 2;
		int lValue = update(left, right, nodeLeft, nodeMid, node * 2, value);
		int rValue = update(left, right, nodeMid + 1, nodeRight, node * 2 + 1, value);
		return seg[node] = merge(lValue, rValue);
	}
	
	void update(int left, int right, int value){
		update(left, right, 0, sz - 1, 1, value);
		return;
	}
};


string str;
int n, k, m;

unordered_map<int, int> vToIdx; 
set<int> validSet;

int getKcutting(int start){
	if(start < 0 || start + k - 1 >= n)
		return -1;
	int ret = 0;
	for(int i = start; i <= start + k - 1; i++)
		ret = ret * 10 + (str[i] - '0');
	return ret;
}

void initializeMapsAndValidSet(){
	for(int i = 0; i < n; i++){
		int value = getKcutting(i);
		if(value != -1)
			validSet.insert(value);
	}	
	for(int i = 0; i < n; i++){
		char tmp = str[i];
		str[i] = '1';
		for(int j = i - k + 1; j <= i; j++){
			int value = getKcutting(j);
			if(value != -1)
				validSet.insert(value);
		}
		str[i] = tmp;
	}
	int idx = 0;
	for(int ele: validSet)
		vToIdx[ele] = idx++;
	return;
}


void computeOneKcutting(int value, RMQ& rmq, int change){
	auto up = validSet.upper_bound(value + m);
	up--;
	rmq.update(vToIdx[value], vToIdx[*up], change);
	return;
}

int getAnswer(){	
	initializeMapsAndValidSet();		
	vector<int> vt = vector<int>(vToIdx.size(), 0);
	RMQ rmq(vt);
	
	for(int i = 0; i < n; i++){
		int value = getKcutting(i);
		if(value != -1)
			computeOneKcutting(value, rmq, 1);
	}
	
	int maxValue = rmq.query();

	for(int i = 0; i < n; i++){
		if(str[i] == '1')
			continue;
		
		for(int j = i - k + 1; j <= i; j++){
			int value = getKcutting(j);
			if(value != -1)
				computeOneKcutting(value, rmq, -1);
		}
		
		char tmp = str[i];
		str[i] = '1';
		
		for(int j = i - k + 1; j <= i; j++){
			int value = getKcutting(j);
			if(value != -1)
				computeOneKcutting(value, rmq, 1);
		}		
		
		maxValue = max(maxValue, rmq.query());
		
		for(int j = i - k + 1; j <= i; j++){
			int value = getKcutting(j);
			if(value != -1)
				computeOneKcutting(value, rmq, -1);
		}
		
		str[i] = tmp;
		
		for(int j = i - k + 1; j <= i; j++){
			int value = getKcutting(j);
			if(value != -1)
				computeOneKcutting(value, rmq, 1);
		}
	}
	return maxValue;
}

int main(){
	freopen("input2.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		
		// inputs
		str.clear();
		vToIdx.clear();
		validSet.clear();
		cin >> n >> k >> m;
		cin >> str;
		
		// outputs
		cout << getAnswer() << "\n";		
	}
	
	return 0;
}

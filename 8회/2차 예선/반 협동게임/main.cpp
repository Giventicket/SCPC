#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int N;
int groups[300000];
vector<int> groups_to_idx[300001];
pair<int, int> st_and_e[300001];

void input() {	
	// cout << "input" << endl;
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> groups[i];
	}
	
	for (int i = 1; i <= N; i++) {
		groups_to_idx[i].clear();
	}
	
	for (int i = 0; i < N; i++) {
		groups_to_idx[groups[i]].push_back(i);
	}
	
	for (int i = 1; i <= N; i++) {
		st_and_e[i] = make_pair(0, groups_to_idx[i].size() - 1);
	}
	return;
}


void solve() {
	vector<int> indices;
	indices.resize(N);
	for (int i = 0; i < N; i++)
		indices[i] = i;
	RMQ rmq(indices);
	int here = 0;
	long long int answer = 0;
	while (here < N) {
		int group = groups[here];
		if (st_and_e[group].first >= st_and_e[group].second) {
			here++;
			continue;
		}
		
		int next = groups_to_idx[group][st_and_e[group].second];
		answer += rmq.query(next, next) - rmq.query(here, here);
		rmq.update(next + 1, N - 1, -1);
		st_and_e[group].first++;
		st_and_e[group].second--;
		here++;
	}
	
	cout << answer << "\n";
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
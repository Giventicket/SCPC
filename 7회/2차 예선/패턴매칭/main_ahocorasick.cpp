#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int ll;

ll N, K, L;
string S;
vector<string> Ps;
vector<int> alphabet_to_pos, prev_S;
vector<vector<int>> prev_Ps;
vector<map<int, int>> go_to; // cur state - { (transition, next state) }
vector<int> depth;
vector<int> failure; 
vector<ll> outputs;

void input() {
	go_to.clear();
	failure.clear();
	outputs.clear();
	depth.clear();
	
	cin >> N >> K;
	cin >> S;
	Ps.clear();
	Ps.resize(K);
	
	L = 0;
	for(int i = 0; i < K; i++) {
		cin >> Ps[i];
		L += Ps[i].size();
	}
		
	return;
}

void renew_prev_S() {	
	int n = S.size();
	prev_S.clear();
	prev_S = vector<int>(n, 0);
	alphabet_to_pos.clear();
	alphabet_to_pos = vector<int>(26, -1);
	for(int i = 0; i < n; i++) {
		int cur = S[i] - 'a';
		if (alphabet_to_pos[cur] != -1)
			prev_S[i] = i - alphabet_to_pos[cur]; // distance from p[i]: smallest value of i - j if p[i] == p[j] and j is in [0, i - 1]. 
		alphabet_to_pos[cur] = i;
	}
	
	return;
}

void renew_prev_Ps() {
	prev_Ps.clear();
	for (string& P: Ps) {
		int m = P.size();
		vector<int> prev_P(m, 0);
		alphabet_to_pos.clear();
		alphabet_to_pos = vector<int>(26, -1);
		for(int i = 0; i < m; i++) {
			int cur = P[i] - 'a';
			if (alphabet_to_pos[cur] != -1)
				prev_P[i] = i - alphabet_to_pos[cur]; // distance from p[i]: smallest value of i - j if p[i] == p[j] and j is in [0, i - 1]. 
			alphabet_to_pos[cur] = i;
		}
		prev_Ps.push_back(prev_P);
	}
	
	return;
}

void build_automation() {
	// go_to
	go_to.resize(L + 1);
	depth.resize(L + 1);
	outputs.resize(L + 1);
	
	int state_cnt = 0, state;
	for (int i = 0; i < prev_Ps.size(); i++) {
		vector<int>& prev_P = prev_Ps[i]; 
		state = 0;
		// cout << Ps[i] << endl;
		for (int& transition: prev_P) {
			if (go_to[state].count(transition) == 0) {
				state_cnt++; 
				go_to[state][transition] = state_cnt;
				depth[go_to[state][transition]] = depth[state] + 1;
				state = go_to[state][transition];
			} else
				state = go_to[state][transition];
		}	
		outputs[state] += (i + 1);
	}
	
	// failure
	failure = vector<int>(state_cnt + 1, -1);
	failure[0] = -1;
	queue<int> q;
	for(pair<int, int> p: go_to[0]) {
		int transition = p.first;
		int next_state = p.second;
		q.push(next_state);
		failure[next_state] = 0;
	}
	
	while (!q.empty()) {
		int cur_state = q.front();
		q.pop();
		for(pair<int, int> p: go_to[cur_state]) {
			int transition = p.first;
			int next_state = p.second;
			
			q.push(next_state);
			int fail = cur_state;
			do {
				fail =  failure[fail];
				if (transition > depth[fail])
					transition = 0;
			} while(go_to[fail].find(transition) == go_to[fail].end() && fail != -1);
			
			if (fail == -1)
				failure[next_state] = 0;
			else {
				failure[next_state] = go_to[fail][transition];
				outputs[next_state] += outputs[failure[next_state]];
			}			
		}
	}
	return;
}

int get_next_state(int state, int transition) {
	if (transition > depth[state])
		transition = 0;
	
	if (go_to[state].find(transition) != go_to[state].end()) {
		return go_to[state][transition];
	}
	
	int fail = state;
	do {
		fail =  failure[fail];
		if (transition > depth[fail])
			transition = 0;
	} while(go_to[fail].find(transition) == go_to[fail].end() && fail != -1);
	if (fail == -1)
		return 0;
	else
		return go_to[fail][transition];
}

ll aho_corasick() {
	build_automation();
	ll ret = 0;
	int state = 0;
	for (int i = 0; i < S.size(); i++) {
		int transition = prev_S[i];
		state = get_next_state(state, transition);
		if (state == -1) {
			state = 0;
			continue;
		}
		ret += outputs[state];
	}
	return ret;
}
 
void solve() {
	// cout << "solve" << endl;
	renew_prev_S();
	ll ans = 0;
	renew_prev_Ps();
	cout << aho_corasick() << "\n";
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
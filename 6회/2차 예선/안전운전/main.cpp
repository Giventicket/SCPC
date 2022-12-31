#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define lli long long int  

// maximum segment tree
struct segTree {
	int sz;
	vector<lli> seg, lazy;
	
	void clear () {
		//cout << "clear" << endl;
		seg.clear();
		lazy.clear();
		return;
	}
	
	void init (int len) {
		//cout << "init" << endl;
		clear();
		sz = len;
		seg.resize(sz * 4);
		lazy.resize(sz * 4);
		return;
	}
	
	void propagate (int nl, int nr, int node) {
		//cout << "propagate" << endl;
		if (nl != nr) {
			seg[node * 2] += lazy[node];
			seg[node * 2 + 1] += lazy[node];
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
		return;
	}
	
	void update (int nl, int nr, int node, int left, int right, lli val) {
		//cout << "update" << endl;
		if (nr < left || right < nl)
			return;
		propagate(nl, nr, node);
		if (left <= nl && nr <= right) {
			seg[node] += val;
			lazy[node] += val;
			return;
		}
		int nm = (nl + nr) / 2;
		update(nl, nm, node * 2, left, right, val);
		update(nm + 1, nr, node * 2 + 1, left, right, val);
		seg[node] = max(seg[node * 2], seg[node * 2 + 1]);
		return;
	}
	
	void update (int left, int right, lli val) {
		update(0, sz - 1, 1, left, right, val);
		return;
	}
	
	lli query (int nl, int nr, int node, int left, int right) {
		//cout << "query" << endl;
		if (nr < left || right < nl)
			return 0;
		propagate(nl, nr, node);
		if (left <= nl && nr <= right)
			return seg[node];
		int nm = (nl + nr) / 2;
		lli lval = query(nl, nm, node * 2, left, right);
		lli rval = query(nm + 1, nr, node * 2 + 1, left, right);
		return max(lval, rval);
	}
	
	lli query(int left, int right) {
		if (left > right)
			return query(right, left);
		return query(0, sz - 1, 1, left, right);
	}
	
};

int l, m, n;
vector<pair<lli, lli>> lf, rgt, traj; // (x,y) left, right, trajectory
vector<lli> x_cut, y_cut, L_cut, R_cut; // xs, ys of cut and ranges for cuts([L, R])
struct segTree RMQ; // range maximum query

void input() {
	//cout << "input" << endl;
	cin >> l >> m >> n;
	lli x, y, u, v, i, idx;
	
	lf.clear();
	rgt.clear();
	traj.clear();
	x_cut.clear();
	y_cut.clear();
	L_cut.clear();
	R_cut.clear();
	RMQ.clear();
	
	for (i = 0, x = 0, y = 0; i < l; i++) {
		cin >> u >> v;
		x += u;
		y += v;
		lf.push_back({x, y});
		y_cut.push_back(y);
	}
	
	for (i = 0, x = 0, y = 0; i < m; i++) {
		cin >> u >> v;
		x += u;
		y += v;
		rgt.push_back({x, y});		
		y_cut.push_back(y);
	}
	
	for (i = 0, x = 0, y = 0; i < n; i++) {
		cin >> u >> v;
		x += u;
		y += v;
		traj.push_back({x, y});
		y_cut.push_back(y);
	}
	
	sort(y_cut.begin(), y_cut.end());
	y_cut.erase(unique(y_cut.begin(), y_cut.end()), y_cut.end());
	
	for (i = 0, idx = 0; i < y_cut.size(); i++) {
		while (traj[idx].second < y_cut[i])
			idx++;
		x_cut.push_back(traj[idx].first);
	}
	
	for (i = 0, idx = 0; i < y_cut.size(); i++) {
		while (lf[idx].second < y_cut[i])
			idx++;
		L_cut.push_back(lf[idx].first);
	}
	
	for (i = 0, idx = 0; i < y_cut.size(); i++) {
		while (rgt[idx].second < y_cut[i])
			idx++;
		R_cut.push_back(rgt[idx].first);
	}	
	
	return;
}

void solve() {
	//cout << "solve" << endl;
	// segment tree
	vector<lli> allX;
	for (int i = 0; i < x_cut.size(); i++) {
		allX.push_back((L_cut[i] + x_cut[i]) / 2);
		allX.push_back((R_cut[i] + x_cut[i]) / 2);
		allX.push_back(x_cut[i]);
	}
	
	sort(allX.begin(), allX.end());
	allX.erase(unique(allX.begin(), allX.end()), allX.end());
	
	map<lli, int> x_to_idx;
	for(int i = 0; i < allX.size(); i++)
		x_to_idx[allX[i]] = i;
	
	RMQ.init(x_to_idx.size());
	
	// compute sum of cut
	vector<lli> cut_sum;
	cut_sum.resize(y_cut.size());
	
	if (L_cut[0] <= x_cut[0] && x_cut[0] <= R_cut[0])
		cut_sum[0] = y_cut[0];
	else
		cut_sum[0] = 0;
	
	for (int i = 1; i < cut_sum.size(); i++) {
		if (L_cut[i] <= x_cut[i] && x_cut[i] <= R_cut[i])
			cut_sum[i] = cut_sum[i - 1] + (y_cut[i] - y_cut[i - 1]);
		else
			cut_sum[i] = cut_sum[i - 1];
	}
	
	// online update & find maximum
	lli answer = cut_sum[cut_sum.size() - 1];
	for (int i = cut_sum.size() - 1; i >= 1; i--) {
		lli min_T = (L_cut[i] + x_cut[i]) / 2;
		lli max_T = (R_cut[i] + x_cut[i]) / 2;
		RMQ.update(x_to_idx[min_T], x_to_idx[max_T], y_cut[i] - y_cut[i - 1]);
		if (x_cut[i] != x_cut[i - 1]) 
			answer = max(answer, cut_sum[i - 1] + RMQ.query(x_to_idx[x_cut[i - 1]], x_to_idx[x_cut[i]]));
		//cout << i << " " << min_T << " " << max_T << " " << answer << "\n";
		//cout << i << " update " << x_to_idx[min_T] << " " << x_to_idx[max_T] << "\n";
		//cout << i << " " << x_to_idx[x_cut[i - 1]] << " " << x_to_idx[x_cut[i]] << "\n";
		//cout << i << " query " << x_to_idx[x_cut[i - 1]] << " " << x_to_idx[x_cut[i]] << " " << RMQ.query(x_to_idx[x_cut[i - 1]], x_to_idx[x_cut[i]]) << "\n";
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
	
	for (int t = 1; t <= T; t++) {
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}
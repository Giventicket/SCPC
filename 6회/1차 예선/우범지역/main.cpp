#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // log, exp

using namespace std;

int n;
vector<pair<int, int>> coor;
vector<pair<pair<int, int>, int>> sorted_coor;
vector<long double> p;
vector<long double> sorted_p;
vector<long double> partial_log_sum; // partial sum for (1 - p)s
vector<int> one_count;
int qx, qy;

bool compare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    int ax = a.first.first;
    int ay = a.first.second;
	int bx = b.first.first;
    int by = b.first.second;
	return ax * by - bx * ay > 0; // a cross b
}

void input() {
	cin >> n;
	coor.clear();
	p.clear();	
	coor.resize(n);
	p.resize(n);
	for(int i = 0; i < n; i++)
		cin >> coor[i].first;
	for(int i = 0; i < n; i++)
		cin >> coor[i].second;
	for(int i = 0; i < n; i++)
		cin >> p[i];
	cin >> qx >> qy;
	for(int i = 0; i < n; i++) {
		coor[i].first -= qx;	
		coor[i].second -= qy;
	}		
	sorted_coor.clear();
	for(int i = 0; i < n; i++)
		sorted_coor.push_back({coor[i], i});
	sort(sorted_coor.begin(), sorted_coor.end(), compare);
	sorted_p.clear();
	for(int i = 0; i < n; i++)
		sorted_p.push_back(p[sorted_coor[i].second]);
	partial_log_sum.clear();
	partial_log_sum.resize(n + 1); // partial_log_sum[i]: i 이전 확률까지의 합
	partial_log_sum[0] = 0;
	for (int i = 0; i < n; i++){
		partial_log_sum[i + 1] = partial_log_sum[i] + logl(1 - sorted_p[i]);
	}
	one_count.clear();
	one_count.resize(n + 1);
	one_count[0] = 0; // one_count[i]: i 이전까지 p에 1이 얼마나 등장하는가?
	for (int i = 1; i <= n; i++){
		if (sorted_p[i] == 1)
			one_count[i] = one_count[i - 1] + 1;
		else
			one_count[i] = one_count[i - 1];
	}
	
	
	/* debugs
	for(int i = 0; i < n; i++) {
		cout << sorted_coor[i].first.first << " " << sorted_coor[i].first.second << " " << sorted_coor[i].second << " " << sorted_p[i] << endl;
	}
	*/
	
	return;
}

int incre_pivot (int pivot) {
	return (pivot + 1 + n) % n;
}

long long CCW(int i, int j) { // i cross j
	return sorted_coor[i].first.first * sorted_coor[j].first.second - sorted_coor[j].first.first * sorted_coor[i].first.second;
}

long double get_log_prob(int i, int pivot) {
	long double log_prob = logl(sorted_p[i]);
	int ones = 0;
	if (pivot <= i){
		log_prob += partial_log_sum[i] - partial_log_sum[pivot];
		ones = one_count[i] - one_count[pivot];
	} else {
		log_prob += partial_log_sum[n] - partial_log_sum[pivot] + partial_log_sum[i];
		ones = one_count[n] - one_count[pivot] + one_count[i];;
	} 
	//cout << "get_log_prob " << pivot << " " << i  << " " << log_prob << endl;
	if (ones == 0)
		return log_prob;
	else
		return -1; // negative infinity
}

long double solve() {
	vector<long double> log_probs;
	int pivot = 1;
	for(int i = 0; i < n; i++) { //a_i is fixed
		while(CCW(pivot, i) <= 0 && i != pivot){
			//cout << "while " << pivot << " " << i << endl;
			pivot = incre_pivot(pivot);
		}
		long double log_prob = get_log_prob(i, pivot);
		if (log_prob != -1)
			log_probs.push_back(log_prob);
	}
	if (one_count[n] == 0)
		log_probs.push_back(partial_log_sum[n]);
	long double answer = 0;
	for(long double log_prob: log_probs)
		answer += exp(log_prob);
	answer = 1 - answer;
	return answer;
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	int T;
	cin >> T;
	cout << fixed;
	cout.precision(10);	
	for (int i = 0; i < T; i++) {
		input();
		cout << "Case #" << i + 1 << "\n";
		cout << solve() << "\n";
	}	
	return 0;
}
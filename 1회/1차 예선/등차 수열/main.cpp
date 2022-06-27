#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#define ll long long

using namespace std;

ll getGcd(ll a, ll b){
	if(a < b)
		return getGcd(b, a);
	if(b == 0)
		return a;
	return getGcd(a%b, b);
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T, M;
	cin >> T;	
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		
		//inputs
		cin >> M;		
		vector<ll> seq = vector<ll>(M);
		for(int i = 0; i < M; i++)
			cin >> seq[i];
		
		//outputs
		vector<ll> diff = vector<ll>(M-1);
		for(int i = 0; i < M - 1; i++)
			diff[i] = seq[i + 1] - seq[i];
		
		ll gcd = diff[0];
		for(int i = 0; i < diff.size(); i++)
			gcd = getGcd(gcd, diff[i]);
		
		if(gcd == 0)
			cout << 1 << "\n";
		else{
			set<ll> st;
			for(int i = 1; i <= (ll)sqrt(gcd) + 1; i++)
				if(gcd % i == 0){
					st.insert(i);
					st.insert(gcd / i);
				}			
			cout << st.size() << "\n";	
		}		
	}		
	
	return 0;
}

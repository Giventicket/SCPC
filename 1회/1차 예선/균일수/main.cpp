#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;

vector<bool> pTable;

vector<bool> make_pTable(){
	int max = (int) sqrt(1000000000);
	vector<bool> vt = vector<bool>(max+1, true);
	vt[1] = false;
	set<int> st;

	for(int i = 2; i <= max; i++)
		st.insert(i);

	while(!st.empty()){
		int prime = *(st.cbegin());
		
		for(auto it = st.cbegin(); it != st.cend(); ){
			int mul = *(it);
			if(prime * mul <= max){
				vt[prime * mul] = false;
				if(mul % prime == 0){
					it++;
					st.erase(mul);
				} else
					it++;
			} else{
				it++;
				st.erase(mul);				
			}
		}
	}
	return vt;
}

set<int> getDiv(int N, bool containOne){
	set<int> div;
	for(int i=1; i < pTable.size(); i++){
		if(i >= N)
			break;
		if(N % i == 0){
			div.insert(i);
			div.insert(N/i);	
		}		
	}
	
	if(!containOne)
		div.erase(1);
	return div;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T, N;
	cin >> T;	
	
	pTable = make_pTable();

	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		
		//inputs
		cin >> N;		
			
		//outputs
		if(N == 1){
			cout << 2 << "\n";
			continue;
		}
		
		set<int> answer;
		set<int> div1 = getDiv(N, true);
		int a, b;
		for(auto it1 = div1.begin(); it1 != div1.end(); it1++){
			a = *it1;
			if((N/a) == 1)
				answer.insert(N);
			else if((N/a) == 2)
				continue;
			set<int> div2 = getDiv((N/a)-1, false);
			
			for(auto it2 = div2.begin(); it2 != div2.end(); it2++){
				b = *it2;
				if(b == 1 || b <= a)
					continue;
				int sum = 1;
				for(int i=0; i<30; i++){
					if(sum == (N/a)){
						answer.insert(b);
						break;
					} else if(sum > N)
						break;			
					sum = sum * b + 1;
				}			
			}
			
		}
		
		cout << *answer.begin() << "\n";
			
	}
	
	return 0;
}

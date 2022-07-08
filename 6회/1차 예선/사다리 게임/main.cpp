#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

#define INF 2000000000

using namespace std;

int N, k, m;
vector<tuple<int, int>> vertex;
vector<int> first;
vector<int> last;
vector<tuple<int, int>> adj;

vector<int> getMinBpCnt_i(int idx){
   vector<int> cache[2];
   cache[0] = vector<int>(2 * k + 2 * N, INF); // horizontal direction
   cache[1] = vector<int>(2 * k + 2 * N, INF); // vertical direction
   
   priority_queue<tuple<int, int, bool>> pq;   
   pq.push({0, first[idx], false});
   while(!pq.empty()){
      int bpCnt, u;
      bool dir;
      tie(bpCnt, u, dir) = pq.top();
      bpCnt = -bpCnt;
      pq.pop();
      
      //cout << "inqueue " << " " << dir << " " << u << " " << bpCnt << endl;
      
      if(cache[dir][u] < bpCnt)
         continue;
      // horizontal
      if(dir){         
         int v_horizontal = get<0>(adj[u]);
         if(cache[false][v_horizontal] > bpCnt){
            cache[false][v_horizontal] = bpCnt;
            pq.push({-cache[false][v_horizontal], v_horizontal, false});
         }
      }
      
      // vertical
      int v_vertical = get<1>(adj[u]);
      if(v_vertical != -1 && cache[true][v_vertical] > bpCnt + (int) dir){
         cache[true][v_vertical] = bpCnt + (int) dir;
         pq.push({-cache[true][v_vertical], v_vertical, true});
      }
   }
   
   vector<int> minBpCnt_i = vector<int>(N + 1);
   for(int i = 1; i <= N; ++i)
      minBpCnt_i[i] = min(cache[0][last[i]], cache[1][last[i]]);
   return minBpCnt_i;
}

vector<vector<int>> getMinBpCnt(){
   vector<vector<int>> minBpCnt = vector<vector<int>>(N + 1);
   for(int i = 1; i <= N; ++i)
      minBpCnt[i] = getMinBpCnt_i(i);   
   return minBpCnt;
}

int main(){
   freopen("input.txt", "r", stdin);
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);  
   cout.tie(NULL);
   
   int T;
   cin >> T;
   
   for(int t = 1; t <= T; ++t){
      cout << "Case #" << t << "\n";
      
      vertex.clear();
      first.clear();
      last.clear();
      adj.clear();
      
      // inputs
      cin >> N >> k >> m;
      adj = vector<tuple<int, int>>(2 * k + 2 * N, {-1, -1});
      first = vector<int>(N + 1, -1);
      last = vector<int>(N + 1, -1);
      
      
      for(int i = 1; i <= N; ++i){
         vertex.push_back({-1, i});
         first[i] = vertex.size() - 1;
      }
      
      for(int i = 0; i < k; ++i){
         int a, b;
         cin >> a >> b;
         vertex.push_back({i, a}); // N + 2 * i
         vertex.push_back({i, b}); // N + 2 * i + 1
      }
      
      for(int i = 1; i <= N; ++i){
         vertex.push_back({k, i});
         last[i] = vertex.size() - 1;
      }
      
      // adj 
      for(int i = 0; i < k; ++i){
         get<0>(adj[N + 2 * i]) = N + 2 * i + 1;
         get<0>(adj[N + 2 * i + 1]) = N + 2 * i;
      }
      
      for(int i = 0; i < 2 * k + 2 * N; ++i){
         for(int j = i + 1; j < 2 * k + 2 * N; ++j){
            if(get<1>(vertex[i]) == get<1>(vertex[j])){
               get<1>(adj[i]) = j; 
               break;
            }
         }            
      }
      
      // outputs         
      vector<vector<int>> minBpCnt = getMinBpCnt();

      int answer = 0;
      for(int i = 0; i < m; ++i){
         int a, b;
         cin >> a >> b;
         if(minBpCnt[a][b] != INF)
            answer += minBpCnt[a][b];   
         else
            answer += -1;   
      }
       cout << answer << "\n";      
   }
      
   return 0;
}
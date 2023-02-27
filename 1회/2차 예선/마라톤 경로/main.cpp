#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <cmath>

#define MAXN 100
#define MAXM 100
#define MAXK 10
#define INF 20001

using namespace std;

short dist[MAXN + 1][MAXM + 1][MAXK + 1];

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	short T, M, N, K;
	cin >> T;	
	
	short delX[2] = {0, 1};
	short delY[2] = {1, 0};
	
	//cout << "weight" << " " << "bottleCnt" << " " << "curX" << " " << "curY" << endl;
	for(short t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
	
		// inputs		
		cin >> M >> N >> K;
		vector<vector<short>> h = vector<vector<short>>(N+1, vector<short>(M+1));
		for(short i = 0; i <= N; i++)
			for(short j = 0; j <= M; j++)
				cin >> h[i][j];
			
		for(short i = 0; i <= MAXN; i++)
			for(short j = 0; j <= MAXM; j++)
				for(short k = 0; k <= MAXK; k++)
					dist[i][j][k] = INF;
				
		// outputs
		priority_queue<tuple<short, short, short, short>> pq;
		pq.push({0, 0, 0, 0});
		dist[0][0][0] = 0;
		while(!pq.empty()){
			tuple<short, short, short, short> ele = pq.top();
			pq.pop();
			short weight = -get<0>(ele);
			short bottleCnt = get<1>(ele);
			short curX = get<2>(ele);
			short curY = get<3>(ele);
			
			//cout << weight << " " << bottleCnt << " " << curX << " " << curY << endl;
			
			if(dist[curX][curY][bottleCnt] < weight)
				continue;
				
			for(short iter = 0; iter < 2; iter++){
				short newX = curX + delX[iter];
				short newY = curY + delY[iter];
				
				if(newX > N || newY > M)
					continue;
				
				short newWeight = weight + abs(abs(h[newX][newY]) - abs(h[curX][curY]));
				
				if(dist[newX][newY][bottleCnt] > newWeight){
					dist[newX][newY][bottleCnt] = newWeight;
					pq.push({-newWeight, bottleCnt, newX, newY});
				}
				if(h[newX][newY] < 0 && dist[newX][newY][bottleCnt + 1] > newWeight){
					dist[newX][newY][bottleCnt + 1] = newWeight;
					pq.push({-newWeight, bottleCnt + 1, newX, newY});
				}
			}
		}
		
		cout << dist[N][M][K] << "\n";
		
	}
	
	return 0;
}

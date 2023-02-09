#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll MOD = 1e9+7;
inline void Add(int &a, int b){ a += b; if(a >= MOD) a -= MOD; }

ll Pow(ll a, ll b){
    ll res = 1;
    for(; b; b >>= 1, a = a * a % MOD) if(b & 1) res = res * a % MOD;
    return res;
}

ll N, K, A[505050], S[505050], Fac[505050], Inv[505050];
vector<int> V[505050], D[505050];
ll Comb(int n, int r){ return r <= n ? Fac[n] * Inv[r] % MOD * Inv[n-r] % MOD : 0; }

void Solve(){
    cin >> N >> K;
    for(int i=0; i<=K; i++) V[i].clear(), D[i].clear();
    for(int i=1; i<=N; i++) cin >> A[i], S[i] = S[i-1] + A[i];
    if(S[N] == 0){
        int cnt = 0;
        for(int i=1; i<N; i++) cnt += S[i] == 0;
        cout << Comb(cnt, K-1) << "\n";
        return;
    }
    if(S[N] % K != 0){ cout << 0 << "\n"; return; }

    ll step = S[N] / K;
    for(int i=1; i<=N; i++){
        if(S[i] % step != 0) continue;
        ll q = S[i] / step;
        if(1 <= q && q <= K) V[q].push_back(i);
    }

    V[0].push_back(0); D[0].push_back(1);
    for(int i=1; i<=K; i++){
        if(V[i].empty()){ cout << 0 << "\n"; return; }
        for(int j=0, k=0; j<V[i].size(); j++){
            while(k < V[i-1].size() && V[i-1][k] < V[i][j]) k++;
            D[i].push_back(k ? D[i-1][k-1] : 0);
        }
        for(int j=1; j<D[i].size(); j++) Add(D[i][j], D[i][j-1]);
    }

    int res = D[K].back();
    if(D[K].size() > 1) res -= D[K][D[K].size()-2];
    if(res < 0) res += MOD;

    cout << res << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    const int SZ = 500'000;
    Fac[0] = 1; for(int i=1; i<=SZ; i++) Fac[i] = Fac[i-1] * i % MOD;
    Inv[SZ] = Pow(Fac[SZ], MOD-2); for(int i=SZ-1; i>=0; i--) Inv[i] = Inv[i+1] * (i+1) % MOD;
    int TC; cin >> TC;
    for(int tc=1; tc<=TC; tc++) cout << "Case #" << tc << "\n", Solve();
}
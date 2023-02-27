#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <queue>
#include <math.h>
#include <memory.h>
 
 
int readInt();
long long readLong();
 
 
int N;
long long X[100001], Y[100001];
long double P[100001];
 
void GatherInput() {
    N = readInt();
    for (int i = 1; i <= N; i++) X[i] = readInt();
    for (int i = 1; i <= N; i++) Y[i] = readInt();
    for (int i = 1; i <= N; i++) scanf("%Lf", &P[i]);
    int Qx = readInt();
    int Qy = readInt();
    for (int i = 1; i <= N; i++) {
        X[i] -= Qx;
        Y[i] -= Qy;
    }
}
 
long long QuadrantOrdinal(long long x, long long y) {
    if (x > 0 && y == 0) return 0;
    if (x > 0 && y > 0) return 1;
    if (x == 0 && y > 0) return 2;
    if (x < 0 && y > 0) return 3;
    if (x < 0 && y == 0) return 4;
    if (x < 0 && y < 0) return 5;
    if (x == 0 && y < 0) return 6;
    if (x > 0 && y < 0) return 7;
    return -1; // x == 0 && y == 0
}
long long QuadrantOrdinal(int i) {
    return QuadrantOrdinal(X[i], Y[i]);
}
 
long long CCW(int i, int j) {
    return (X[i] * Y[j] - X[j] * Y[i]);
}
 
int IncMod(int x, int delta, int mod) {
    auto val = (x + delta + mod) % mod;
    if (val == 0) val = mod;
    return val;
}
 
int A[100000];
long double P_sum[100001]; // 'log(1 - P[i])'의 prefix sum (P[i] == 1인 경우 -INF 대신 0으로)
int P_one[100001]; // P[i] == 1인 것들의 prefix sum (각 항목: P[i] == 1인 경우에는 1, 아니면 0)
 
long long tmp1[100001], tmp2[100001];
 
void Solve() {
    /* step 1 */
    for (int i = 1; i <= N; i++) A[i] = i;
    std::sort(A + 1, A + N + 1, [](const int i, const int j) -> bool {
        auto i_qo = QuadrantOrdinal(i);
        auto j_qo = QuadrantOrdinal(j);
        if (i_qo != j_qo) return i_qo < j_qo;
 
        return CCW(i, j) > 0;
    });
 
    /* step 1b */
    memcpy(tmp1, X, sizeof(X));
    memcpy(tmp2, Y, sizeof(Y));
    memcpy(P_sum, P, sizeof(P));
    for (int i = 1; i <= N; i++) {
        int j = A[i];
        X[i] = tmp1[j];
        Y[i] = tmp2[j];
        P[i] = P_sum[j];
    }
 
    /* step 2 */
    P_sum[0] = 0;  P_one[0] = 0;
    for (int i = 1; i <= N; i++) {
        if (P[i] == 1) {
            P_sum[i] = P_sum[i - 1];
            P_one[i] = P_one[i - 1] + 1;
        }
        else {
            P_sum[i] = P_sum[i - 1] + logl(1 - P[i]);
            P_one[i] = P_one[i - 1];
        }
    }
 
    /* step 3 */
    std::vector<long double> probs;
    int next = 1;
    for (int i = 1; i <= N; i++) {
        while (i != IncMod(next, 1, N) && CCW(i, IncMod(next, 1, N)) > 0) {
            next = IncMod(next, 1, N);
        }
 
        long double log_prob = logl(P[i]);
        int one_count = 0;
        if (i <= next) { /* [1..i) and (next..N] */
            log_prob += (P_sum[i - 1] - P_sum[0]) + (P_sum[N] - P_sum[next]);
            one_count += (P_one[i - 1] - P_one[0]) + (P_one[N] - P_one[next]);
        }
        else { /* (next..i) */
            log_prob += (P_sum[i - 1] - P_sum[next]);
            one_count += (P_one[i - 1] - P_one[next]);
        }
 
        if (one_count == 0) { /* feasible */
            long double prob = expl(log_prob);
            probs.push_back(prob);
        }
    }
    if (P_one[N] == 0) probs.push_back(expl(P_sum[N]));
 
    /* step 4 */
    std::sort(probs.begin(), probs.end());
    long double ans = 0;
    for (auto pp : probs) ans += pp;
    ans = 1 - ans;
 
    /* step 5 */
    printf("%.10Lf\n", ans);
}
 
 
 
int main() {
#ifdef BOJ
    int T = readInt();
#else
    int T = readInt();
    setbuf(stdout, NULL);
#endif
    for (int test_case = 1; test_case <= T; test_case++) {
        GatherInput();
#ifndef BOJ
        printf("Case #%d\n", test_case);
#endif
        Solve();
    }
    return 0;
}
 
int readInt() {
    int p;
    scanf("%d", &p);
    return p;
}
 
long long readLong() {
    long long p;
    scanf("%lld", &p);
    return p;
}

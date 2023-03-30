# https://blog.kyouko.moe/m/74

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
 
struct Mint
{
    static const int MOD = 998'244'353;
    static const int prr = 3;
 
    Mint() : _v(0) {}
    Mint(int v) : _v((v % MOD + MOD) % MOD) {}
    int val() const { return _v; }
 
    Mint &operator+=(const Mint &rhs)
    {
        _v += rhs._v;
        if (_v >= MOD)
            _v -= MOD;
        return *this;
    }
    Mint &operator-=(const Mint &rhs)
    {
        _v -= rhs._v;
        if (_v < 0)
            _v += MOD;
        return *this;
    }
    Mint &operator*=(const Mint &rhs)
    {
        _v = (long long)_v * rhs._v % MOD;
        return *this;
    }
    Mint &operator/=(const Mint &rhs) { return *this = *this * rhs.inv(); }
 
    Mint operator+() const { return *this; }
    Mint operator-() const { return Mint() - *this; }
 
    Mint pow(long long n) const
    {
        assert(0 <= n);
        Mint x = *this, r = 1;
        while (n)
        {
            if (n & 1)
                r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    Mint inv() const
    {
        assert(_v);
        return pow(MOD - 2);
    }
    friend Mint operator+(const Mint &lhs, const Mint &rhs) { return Mint(lhs) += rhs; }
    friend Mint operator-(const Mint &lhs, const Mint &rhs) { return Mint(lhs) -= rhs; }
    friend Mint operator*(const Mint &lhs, const Mint &rhs) { return Mint(lhs) *= rhs; }
    friend Mint operator/(const Mint &lhs, const Mint &rhs) { return Mint(lhs) /= rhs; }
    friend bool operator==(const Mint &lhs, const Mint &rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const Mint &lhs, const Mint &rhs) { return lhs._v != rhs._v; }
 
    static Mint w(int n)
    {
        assert((MOD - 1) % n == 0);
        return Mint(prr).pow((MOD - 1) / n);
    }
 
private:
    int _v;
};
 
template <class F>
void fft(vector<F> &a, bool inv)
{
    int N = a.size(), j = 0;
    vector<F> roots(N / 2);
    for (int i = 1; i < N; i++)
    {
        int bit = N >> 1;
        while (j >= bit)
        {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }
 
    F w = F::w(N);
    if (inv)
        w = w.inv();
    for (int i = 0; i < N / 2; i++)
        roots[i] = i ? w * roots[i - 1] : F(1);
 
    for (int i = 2; i <= N; i <<= 1)
    {
        int step = N / i;
        for (int j = 0; j < N; j += i)
            for (int k = 0; k < i / 2; k++)
            {
                F u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
                a[j + k] = u + v;
                a[j + k + i / 2] = u - v;
            }
    }
}
 
template <class F>
vector<F> convolution(vector<F> a, vector<F> b)
{
    int n = int(a.size()), m = int(b.size());
    if (!n || !m)
        return {};
    int z = 2;
    while (z < n + m - 1)
        z <<= 1;
 
    a.resize(z), fft(a, false);
    b.resize(z), fft(b, false);
    for (int i = 0; i < z; i++)
        a[i] *= b[i];
    fft(a, true), a.resize(n + m - 1);
 
    F iz = F(z).inv();
    for (int i = 0; i < n + m - 1; i++)
        a[i] *= iz;
 
    return a;
}
 
template <class F, vector<F> (*conv)(vector<F>, vector<F>)>
class Polynomial
{
    vector<F> p;
 
public:
    Polynomial() : p() {}
    Polynomial(vector<F> v) : p(v) {}
    int deg() const { return (int)p.size() - 1; }
    F &operator[](int idx) { return p[idx]; }
    const F &operator[](int idx) const { return p[idx]; }
 
    void set_degree(int deg)
    {
        assert(deg >= -1);
        p.resize(deg + 1);
    }
 
    Polynomial operator+(const Polynomial &rhs) const
    {
        Polynomial ret = *this;
        if (ret.deg() < rhs.deg())
            ret.set_degree(rhs.deg());
        for (int i = 0; i <= rhs.deg(); i++)
            ret[i] += rhs[i];
        return ret;
    }
    Polynomial &operator+=(const Polynomial &rhs)
    {
        if (deg() < rhs.deg())
            set_degree(rhs.deg());
        for (int i = 0; i <= rhs.deg(); i++)
            p[i] += rhs[i];
        return *this;
    }
 
    Polynomial operator*(const Polynomial &rhs) const { return Polynomial(conv(p, rhs.p)); }
    Polynomial &operator*=(const Polynomial &rhs)
    {
        p = move(conv(p, rhs.p));
        return *this;
    }
 
    Polynomial inv(int degree = -1) const
    {
        if (degree == -1)
            degree = deg();
        assert(deg() >= 0 && degree >= 0 && p[0] == F(1));
 
        Polynomial a({F(1)});
        for (int l = 1; l <= degree; l *= 2)
        {
            Polynomial p0 = vector(p.begin(), p.begin() + min(l, (int)p.size()));
            Polynomial p1;
            if ((int)p.size() >= l)
                p1 = vector(p.begin() + l, p.begin() + min(2 * l, (int)p.size()));
 
            Polynomial ap0 = a * p0;
            Polynomial c = vector(ap0.p.begin() + l, ap0.p.end());
 
            Polynomial b = a * p1;
            b.set_degree(l - 1);
            b += c;
            b *= a;
            b.set_degree(l - 1);
            a.p.resize(2 * l);
            for (int i = l; i < 2 * l; i++)
                a.p[i] -= b[i - l];
        }
        a.set_degree(degree);
        return a;
    }
};
 
using Poly = Polynomial<Mint, convolution<Mint>>;
 
int solve(int K, vector<Mint> p)
{
    int N = p.size();
    Mint P = 0;
    for (Mint x : p)
        P += x;
    for (Mint &x : p)
        x = P - x;
 
    function<pair<Poly, Poly>(int, int)> mul = [&](int s, int e)
    {
        if (s == e)
            return make_pair(Poly({1}), Poly({1, -p[s]}));
        auto [lu, ld] = mul(s, (s + e) / 2);
        auto [ru, rd] = mul((s + e) / 2 + 1, e);
        return make_pair(lu * rd + ru * ld, ld * rd);
    };
 
    auto [u, d] = mul(0, N - 1);
    u *= d.inv(K);
 
    int ans = 0;
    for (int i = 1; i <= K; i++)
        ans ^= (Mint(N) * P.pow(i) - u[i]).val();
 
    return ans;
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        int N, K;
        cin >> N >> K;
        vector<Mint> p(N);
        for (Mint &x : p)
        {
            int v;
            cin >> v;
            x = v;
        }
        int ans = solve(K, p);
        cout << "Case #" << tc << '\n'
             << ans << endl;
    }
}
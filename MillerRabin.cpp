#include <bits/stdc++.h>
#define NAME "MillerRabin"
using namespace std;
typedef pair<int, int> pairII;
#define X first
#define Y second
#define Fort(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define Ford(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

set<long long> checkSet = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

long long Rand(long long l, long long r)
{
    assert(l <= r);
    return l + rand() % (r - l + 1);
}

long long Power(long long a, long long b, long long MOD)
{
    if (b == 1) return a % MOD;
    if (b == 0) return 1LL;

    long long tmp = Power(a, b / 2, MOD);
    tmp = tmp * tmp % MOD;

    if (b % 2 == 1) return tmp * a % MOD;
    return tmp;
}

bool Test(long long a, long long n, long long k, long long m)
{
    long long mod = Power(a, m, n);

    if (mod == 1 || mod == n - 1)
        return 1;

    Fort(l, 1, k - 1)
    {
        mod *= mod;
        mod %= n;

        if (mod == n - 1)
            return 1;
    }

    return 0;
}

bool MillerRabin(long long n)
{
    if (n < 2) return 0;

    long long k = 0, m = n - 1;

    while (m % 2 == 0)
    {
        m /= 2;
        k++;
    }

    for(long long a : checkSet)
    {
        if (n == a) return 1;
        if (!Test(a, n, k, m))
            return 0;
    }

    return 1;
}

bool IsPrime(long long n)
{
    if (n < 2) return 0;

    for(long long x = 2; x * x <= n; x++)
        if (n % x == 0) return 0;

    return 1;
}

void Read()
{

}

void init()
{

}

void Solve()
{

}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    srand(time(0));

    long long q = 10;
    while (q--)
    {
        long long n = Rand(1, 1e16);
        if (IsPrime(n) != MillerRabin(n))
        {
            cout << "It's wrong code if n = " << n << "\n";
        }
    }

    return 0;
}



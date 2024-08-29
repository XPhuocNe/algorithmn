#include <bits/stdc++.h>
#define NAME "XPhuoc"

using namespace std;

#define X first
#define Y second
#define pb push_back
#define Fort(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define Ford(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)

typedef pair<int, int> pairII;

template <typename T>
bool maximize(T &x, T y, T None = -1)
{
    if (!(x < y) && x != None)
        return 0;

    x = y;
    return 1;
}

template <typename T>
bool minimize(T &x, T y, T None = -1)
{
    if (x <= y && x != None)
        return 0;

    x = y;
    return 1;
}

/*..............................................................................................................................................*/
struct Pizzas
{
    long long t, a, b;

    Pizzas(long long _t = 0, long long _a = 0, long long _b = 0):
        t(_t), a(_a), b(_b) {};

    bool operator < (const Pizzas &other) const
    {
        return t < other.t;
    }
};

struct Lines
{
    long long a, b;

    Lines(long long _a = 0, long long _b = 0):
        a(_a), b(_b) {};

    long long query(long long x)
    {
        return a * x + b;
    }
};

struct ConvexHullTrick
{
    vector<Lines> cht;
    int n = 0;

    bool better(Lines x, Lines y, Lines z)
    {
        return (z.b - y.b) * (x.a - y.a) <= (y.b - x.b) * (y.a - z.a);
    }

    void add(Lines ln)
    {
        while (n > 1 && better(cht[n - 2], cht[n - 1], ln))
        {
            cht.pop_back();
            n--;
        }

        cht.push_back(ln);
        n++;
    }

    long long query(long long x)
    {
        long long result = cht[0].query(x);

        int l = 0;
        int r = n - 1;

        while (l < r)
        {
            int m = (l + r) / 2;

            long long a = cht[m].query(x);
            long long b = cht[m + 1].query(x);

            maximize(result, max(a, b));

            if (a > b)
                r = m - 1;
            else l = m + 1;
        }

        return result;
    }
};

const int N = 1e5, MAX = 1e5;
const long long INF = 1e16;

int n;
Pizzas pizza[N + 7];
long long pSB[N + 7], pSC[N + 7];

long long w;

void Read()
{
    cin >> n >> w;

    Fort(i, 1, n)
        cin >> pizza[i].t >> pizza[i].a >> pizza[i].b;
}

void init()
{

}

void Solve()
{
    sort(pizza + 1, pizza + n + 1);

    vector<long long> dp(n + 2, -INF);

    ConvexHullTrick CHT;

    CHT.add({0, 0});

    Fort(i, 1, n)
    {
        long long t = pizza[i].t;
        long long a = pizza[i].a;
        long long b = pizza[i].b;

        pSB[i] = pSB[i - 1] + b;
        pSC[i] = pSC[i - 1] + a + b * t;

        maximize(dp[i], CHT.query(t) - t * pSB[i] + pSC[i] - w);

        CHT.add({pSB[i], -pSC[i] + dp[i]});

        cout << dp[i] << "\n";
    }

    cout << dp[n] << "\n";

}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    #ifndef ONLINE_JUDGE
        freopen(NAME".INP", "r", stdin);
        freopen(NAME".OUT", "w", stdout);
    #endif // ONLINE_JUDGE

    int TEST = 1;

    if (TEST == 0)
        cin >> TEST;

    while (TEST--)
    {
        Read();
        init();
        Solve();
    }

    return 0;
}

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

struct IntervalTree
{
    static const long long INF = 1e16;
    int n;
    vector<int> low, high;
    vector<Lines> node;

    void build(int id, int l, int r)
    {
        low[id] = l;
        high[id] = r;

        if (l == r)
            return ;

        int mid = (l + r) / 2;

        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
    }

    IntervalTree(int _n): n(_n)
    {
        int I = 4 * n;

        low.resize(I, 0);
        high.resize(I, 0);

        node.resize(I, {0, -INF});

        build(1, 1, n);
    }

    long long query(long long id, long long x)
    {
        if (low[id] > x || high[id] < x)
            return -INF;

        if (low[id] == high[id])
            return node[id].query(x);

        return max({node[id].query(x), query(id * 2, x), query(id * 2 + 1, x)});
    }

    void update(int id, int u, int v, Lines ln)
    {
        if (low[id] > v || high[id] < u)
            return ;

        if (u <= low[id] && high[id] <= v)
        {
            int mid = (low[id] + high[id]) / 2;

            long long nodeLow = node[id].query(low[id]);
            long long nodeHigh = node[id].query(high[id]);
            long long nodeMid1 = node[id].query(mid);
            long long nodeMid2 = node[id].query(mid + 1);

            long long lineLow = ln.query(low[id]);
            long long lineHigh = ln.query(high[id]);
            long long lineMid1 = ln.query(mid);
            long long lineMid2 = ln.query(mid + 1);

            if (nodeLow >= lineLow && nodeHigh >= lineHigh)
                return ;

            if (nodeLow <= lineLow && nodeHigh <= lineHigh)
            {
                node[id] = ln;
                return ;
            }

            if (nodeLow >= lineLow && nodeMid1 >= lineMid1)
            {
                update(id * 2 + 1, u, v, ln);
                return ;
            }

            if (nodeLow <= lineLow && nodeMid1 <= lineMid1)
            {
                update(id * 2 + 1, u, v, node[id]);
                node[id] = ln;
                return ;
            }


            if (nodeMid2 >= lineMid2 && nodeHigh >= lineHigh)
            {
                update(id * 2, u, v, ln);
                return ;
            }

            if (nodeMid2 <= lineMid2 && nodeHigh <= lineHigh)
            {
                update(id * 2, u, v, node[id]);
                node[id] = ln;

                return ;
            }
        }

        update(id * 2, u, v, ln);
        update(id * 2 + 1, u, v, ln);
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

    IntervalTree IT(MAX);

    pSB[0] = 0;
    pSC[0] = 0;

    IT.update(1, 1, MAX, {0, 0});

    Fort(i, 1, n)
    {
        long long t = pizza[i].t;
        long long a = pizza[i].a;
        long long b = pizza[i].b;

        pSB[i] = pSB[i - 1] + b;
        pSC[i] = pSC[i - 1] + a + b * t;

        maximize(dp[i], IT.query(1, t) - t * pSB[i] + pSC[i] - w);

        IT.update(1, 1, MAX, {pSB[i], -pSC[i] + dp[i]});
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

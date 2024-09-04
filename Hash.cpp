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
bool maximize(T &x, T &y, T None = -1)
{
    if (!(x < y) && x != None)
        return 0;

    x = y;
    return 1;
}

template <typename T>
bool minimize(T &x, T &y, T None = -1)
{
    if (x <= y && x != None)
        return 0;

    x = y;
    return 1;
}

/*..............................................................................................................................................*/

const int N = 1e5;
const long long INF = 1e16 + 7;
int n, m;

string a, b;

struct Hash
{
    /*Nho goi Hash::init() */		

    static const int N = 1e6;
    static const long long base = 37, MOD = 1e9 + 270307;
    static long long exp[N + 2];

    int n;
    string S;
    vector<long long> has;

    Hash(int _n = 0, string _S = ""): n(_n), S(_S)
    {
        has.resize(n + 2, 0);

        has[0] = 0;

        Fort(i, 1, n)
            has[i] = (has[i - 1] * base + (S[i] - 'a' + 1)) % MOD;
    }

    static void init()
    {
        exp[0] = 1;

        Fort(i, 1, N)
            exp[i] = exp[i - 1] * base % MOD;
    }

    long long query(int l, int r)
    {
        return (has[r] - has[l - 1] * exp[r - l + 1] % MOD + MOD * MOD) % MOD;
    }
};

long long Hash::exp[N + 2];


void Read()
{
    cin >> a;
    cin >> b;
}

void init()
{
    n = a.size();
    a = ' ' + a;

    m = b.size();
    b = ' ' + b;

    Hash::init();
}

void Solve()
{
    Hash ar(n, a);
    Hash br(m, b);

    Fort(r, m, n)
        if (ar.query(r - m + 1, r) == br.query(1, m))
            cout << r - m + 1 << " ";
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

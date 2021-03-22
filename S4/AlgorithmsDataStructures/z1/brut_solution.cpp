#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxm = int(1e6) + 10;
const ll k = 25;

vector < pair <int, int> > sznurki;
int ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m,n,d;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        cin >> d >> n;
        sznurki.pb(mp(-d,n));
    }

    sort(sznurki.begin(), sznurki.end());

    priority_queue <pair <int, int> > q;

    for (auto s: sznurki)  q.push(s);

    while(!q.empty())
    {
        pair <int, int> mini = q.top();
        q.pop();
        while (!q.empty() and q.top().first == mini.first)
        {
            mini.second += q.top().second;
            q.pop();
        }
        if (mini.second % 2 == 1) ans++;
        if (mini.second > 1)
        {
            q.push(make_pair(mini.first*2, mini.second/2));
        }
   }

    cout << ans;
    return 0;
} 
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

vector < pair <ll, ll> > sznurki;
int ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll m,n,d;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        cin >> d >> n;
        sznurki.pb(mp(-d,n));
    }

    sort(sznurki.begin(), sznurki.end());

    priority_queue <pair <ll, ll> > q;

    for (auto s: sznurki)  q.push(s);

    while(!q.empty())
    {
        pair <ll, ll> mini = q.top();
        pair <ll, ll> mini2;
        q.pop();
        if(!q.empty())
        {
            mini2 = q.top();
        }
        if (!q.empty() and mini2.first == mini.first)
        {
            mini.second += mini2.second;
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
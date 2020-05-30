#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 100005;
int n,m,a,b,c,q;

vector <pair <int, int> > g[maxn];

int longestPaths[maxn];
int minimumPairs[maxn];

int maxPath(int v)
{
    if (longestPaths[v]) return longestPaths[v];
    longestPaths[v] = 1;
    for (auto u:g[v])
    {
        if (maxPath(u.first) + 1 > longestPaths[v])
        {
            longestPaths[v] = longestPaths[u.first] + 1;
            minimumPairs[v] = max(u.second, minimumPairs[u.first]);
        }
    }
    return longestPaths[v];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    int n_og = n;
    for (int i = 1; i <= m; i++)
    {
        cin>>a>>b;
        g[a].pb({b,i});
    }
    int ans = maxn;
    for (int i = 1; i<=n; i++)
    {
        if(maxPath(i) == n) ans = min(ans, minimumPairs[i]);
    }
    if (ans == maxn) cout<<-1;
    else cout<<ans;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
const ll inf = 1e17 + 10;
ll n, a, b, c, curr_maks, curr_mini, maks = -inf, mini = inf;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>a>>b;
    for(ll i=0; i<n; i++){
        cin>>c;
        curr_maks+=c;
        curr_mini+=c;
        maks = max(maks, curr_maks);
        mini = min(mini, curr_mini);
        if(curr_mini>0) curr_mini = 0;
        if(curr_maks<0) curr_maks = 0;
    }
    cout<<max(a*mini + b, a*maks + b);
    return 0;
}
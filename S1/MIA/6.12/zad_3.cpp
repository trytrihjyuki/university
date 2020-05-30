#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1005;
const ll k = 25;
ll n,m,a,b;

priority_queue <ll> clusters;
vector <ll> arrays;
ll bity[100];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(ll i=0; i<n; i++){
        cin>>a;
        for(ll i=0; i<=30; i++){
            if((1<<i)&a) bity[i]++;
        }
    }
    for(ll i=0; i<m; i++){
        cin>>b;
        arrays.pb(b);
    }
    sort(arrays.begin(), arrays.end());
    ll ans = 0;
    for(ll i=0; i<arrays.sz; i++){
        ll itek = arrays[i];
        while(itek<100&&!bity[itek]) itek++;
        if(itek==100) break;
        bity[itek]--;
        for(ll j=arrays[i]; j<itek; j++) bity[j]++;
        ans++;
    }
    cout<<ans;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll zeroo = 1800;
const ll maxn = zeroo*2;
const ll mod = 1000000007;
const ll infi = 1000000007;
ll a,b;
vector <ll> v;
string s;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>a;
    for(int i=0; i<a; i++){
        cin>>b;
        v.pb(b);
    }
    ll ans = 0;
    ll poprzedni = v[v.sz-1];
    ans+=poprzedni;
    for(int i=v.sz-2; i>=0; i--){
        ans+=max(min(poprzedni-1,v[i]),1LL*0);
        poprzedni=max(min(poprzedni-1,v[i]),1LL*0);
    }   
    cout<<ans;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
ll t;
ll  n,k,m;
ll mult(ll a, ll b){
    ll wyn = 0;
    while(b>0){
        if(b&1) wyn = (wyn + a)%m;
        a = (a*2)%m;
        b/=2;
    }
    return wyn;
}
ll pot(ll n, ll k){
    ll wyn = 1;
    while(n>0){
        if(n%2)
            wyn = mult(wyn,k);
        n/=2;
        k = mult(k,k);
    }
    return wyn;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>k>>m;
        k = k%m;
        cout<<pot(n,k)<<"\n";
    }
    return 0;
}
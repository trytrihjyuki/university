#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1005;
const ll infi = 1000000000;
int n,a,b,c,m,k;
int x;
int armia_ziomala;
bool can_friend(int x){
    int roznia = 0;
    for(int i=0; i<=20; i++){
        if(((1<<i)&x)^((1<<i)&armia_ziomala)) roznia++;
    }
    if(roznia<=k) return 1;
    else return 0;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    vector <int> x_v;
    for(int i=0; i<m; i++){
        cin>>a;
        x_v.pb(a);
    }
    cin>>armia_ziomala;
    int ans=0;
    for(int i=0 ;i<m; i++){
        if(can_friend(x_v[i])) ans++;
    }
    cout<<ans;
    return 0;
}
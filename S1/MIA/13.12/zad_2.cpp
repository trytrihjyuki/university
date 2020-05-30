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
const ll k = 25;
ll n,a,b,m,a_max,b_max;
ll suma_a,suma_b;
vector <ll> pierwszy;
vector <ll> drugie;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>m>>n;
    for(ll i=0; i<m; i++){
        cin>>a;
        suma_a+=a;
        a_max = max(a_max,a);
        pierwszy.pb(a);
    }

    for(ll i=0; i<n; i++){
        cin>>b;
        suma_b+=b;
        b_max = max(b_max,b);
        drugie.pb(b);
    }
    sort(pierwszy.begin(), pierwszy.end());
    sort(drugie.begin(), drugie.end());
    ll ans_1 = suma_b, ans_2 = suma_a;
    for(ll i=0; i<pierwszy.sz-1; i++) //wrzucam do dużego ziomala w a
        ans_1+=min(pierwszy[i],suma_b);
    for(ll i=0; i<drugie.sz-1; i++)
        ans_2+=min(drugie[i],suma_a);
    cout<<min(ans_2,ans_1);
    return 0;
}
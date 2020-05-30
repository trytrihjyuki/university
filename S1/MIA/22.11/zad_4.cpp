#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 2*1e5 + 100;
const ll k = 17;
const ll infi = 1000000007;
ll d,n,m,a,b;
ll najblizsza_tansza[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>d>>n>>m;
    vector < pair <ll, ll> > v;
    for(ll i=0; i<m; i++){
        ll pozycja,cena;
        cin>>pozycja>>cena;
        v.pb({pozycja,cena});
    }
    v.pb({d,0});
    v.pb({0,0});
    sort(v.begin(), v.end());
    stack <ll> stos;
    stos.push(v.sz-1);
    for(ll i=v.sz-1; i>=0; i--){
        ll kandydat = v.sz-1;
        while(!stos.empty() && v[stos.top()].second > v[i].second) stos.pop();
        if(!stos.empty()) kandydat = stos.top();
        najblizsza_tansza[i] = kandydat;
        stos.push(i);
    }
    deb{
        cout<<"najblizsza_tansza[]:\n";
        for(ll i=0; i<m; i++){
            cout<<i<<".\nv[i].first = "<<v[i].first<<"\nv[i].second: "<<v[i].second<<"\n najblizsza_tansza[i]"<<najblizsza_tansza[i]<<endl<<endl;
        }
    }
    ll ans = 0;
    //symulacja
    ll bak = n;
    for(ll i=1; i<v.sz; i++){
        deb cout<<"Jestem w "<<i<<" mam "<<bak<<" litrów paliwa\n";
        if(i!=0) bak = bak - (v[i].first-v[i-1].first);
        if(bak<0){
            cout<<-1;
            return 0;
        }
        if(bak>=v[najblizsza_tansza[i]].first-v[i].first){ //starczy paliwa do tanszej
            //nic
            deb cout<<"Jestem w "<<i<<" starczy mi paliwa do tańszej.\n";
        }
        else{
            deb cout<<"Jestem w "<<i<<" nie starczy mi paliwa do tańszej.Tankuję "<< min(n,v[najblizsza_tansza[i]].first-v[i].first-bak)<<" litrów po cenie: "<<v[i].second<<endl;
            ans+=1LL*v[i].second * min(n-bak,v[najblizsza_tansza[i]].first-v[i].first-bak);
            bak += min(n-bak,v[najblizsza_tansza[i]].first-v[i].first-bak);
        }
    }
    cout<<ans;
    return 0;
}
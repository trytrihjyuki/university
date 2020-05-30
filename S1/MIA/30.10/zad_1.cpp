#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e18;
const ll k = 25;
ll q,a,b,c,d;
unordered_map <ll, ll> koszt_gora;
// bool exists_map(ll a){
//     map<ll,ll>::iterator it = mapka.find(a);
//     if(it != mapka.end()) return 1;
//     return 0;
// }
void dodaj(ll a, ll b, ll v){
    ll lca;
    ll aa = a;
    ll bb = b;
    while(a!=b){
        if(a>b) a/=2;
        else b/=2;
    }
    lca = a;
    deb cout<<"DODAWANIE: "<<aa<<" "<<bb<<" "<<v<<endl;
    while(aa!=lca){
        deb cout<<"dodaje w koszt_gora["<<aa<<"]: "<<v<<endl;
        koszt_gora[aa]+=v;
        aa/=2;
    }
    while(bb!=lca){
        deb cout<<"dodaje w koszt_gora["<<bb<<"]: "<<v<<endl;
        koszt_gora[bb]+=v;
        bb/=2;
    }
   deb cout<<endl<<endl;
}
ll suma(ll aa, ll bb){
    deb cout<<"SUMAAAAA "<<aa<<" "<<bb<<endl;
    ll ans = 0;
    ll lca;
    ll a = aa;
    ll b = bb;
    while(a!=b){
        if(a>b) a/=2;
        else b/=2;
    }
    lca = a;
  deb  cerr<<aa<<" "<<bb<<" "<<lca<<endl;
    while(aa!=lca){
    deb    cerr<<"dodaje koszt_gora["<<aa<<"]: "<<koszt_gora[aa]<<endl;
        ans+=koszt_gora[aa];
        aa/=2;
    }
    while(bb!=lca){
       deb  cerr<<"dodaje koszt_gora["<<bb<<"]: "<<koszt_gora[bb]<<endl;
        ans+=koszt_gora[bb];
        bb/=2;
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>q;
    for(ll i=0; i<q; i++){
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            dodaj(b,c,d);
        }
        else{
            cin>>b>>c;
            cout<<suma(b,c)<<"\n";
        }
    }
    return 0;
}
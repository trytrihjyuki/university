#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
const ll infi = 1e18 + 10;
ll n,m,x,y,u,v,w,a,b;
ll taxi_koszt[maxn],taxi_zasieg[maxn], koszty[maxn];
vector <pair <ll, ll> > g[maxn];
vector <pair <ll, ll> > g2[maxn];
void dijkstra(ll v_startowy){
    for(ll i=1; i<=n; i++) koszty[i] = infi;
    //koszty[v_startowy] = 0;
    priority_queue <pair <ll, ll> > kolejka;
    kolejka.push({0,v_startowy});
    while(!kolejka.empty()){
        pair <ll, ll> parka = kolejka.top();
        kolejka.pop();
        ll vb = parka.second;
        ll odl = -parka.first;
        if(koszty[vb] > odl){
            koszty[vb] = odl;
            for(auto sonsiad: g[vb]){
                if(odl+sonsiad.second < koszty[sonsiad.first])
                    kolejka.push({-(odl+sonsiad.second),sonsiad.first});
            }
        }
    }
    for(ll i=1; i<=n; i++){
        deb cout<<"odleglosc trasy z "<<v_startowy<<" do "<<koszty[i]<<endl;
        if(i!=v_startowy && koszty[i] <= taxi_zasieg[v_startowy]){
            g2[v_startowy].pb({i,taxi_koszt[v_startowy]});
            //g2[i].pb({v_startowy,taxi_koszt[v_startowy]});
        }
    }
    deb cout<<endl<<endl;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>x>>y;
    for(ll i=0; i<m; i++){
        cin>>u>>v>>w;
        g[v].pb({u,w});
        g[u].pb({v,w});
    }
    for(ll i=1; i<=n; i++){
        cin>>a>>b;
        taxi_zasieg[i] = a;
        taxi_koszt[i] = b;
    }
    for(ll i=1; i<=n; i++) dijkstra(i);
    for(ll i=1; i<=n; i++) koszty[i] = infi;
    //koszty[x] = 0;
    priority_queue <pair <ll, ll> > kolejka;
    kolejka.push({0,x});
    while(!kolejka.empty()){
        pair <ll, ll> parka = kolejka.top();
        kolejka.pop();
        ll vb = parka.second;
        ll odl = -parka.first;
        if(koszty[vb] > odl){
            koszty[vb] = odl;
            for(auto sonsiad: g2[vb]){
                if(odl+sonsiad.second < koszty[sonsiad.first])
                    kolejka.push({-(odl+sonsiad.second),sonsiad.first});
            }
        }
    }
    deb{
        for(ll i=1; i<=n; i++){
            cout<<"from "<<i<<endl;
            for(auto u:g2[i])
                cout<<"("<<u.first<<","<<u.second<<")  ";
            cout<<endl<<endl;
        }
    }
    ll ans = koszty[y] == infi ? -1 : koszty[y];
    cout<<ans;
    return 0;
}
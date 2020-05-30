#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e5 + 100;
const ll infi = 9223372036854775800;
int n,m,a,b,d;
int tab[maxn];
vector < pair <int, int> > g[maxn];
ll koszt[maxn];
ll poprzednik[maxn], drogowskazy[maxn], drogowskazy2[maxn];
priority_queue < pair <ll, ll> > kolejka;
void dijkstra(){
    koszt[1] = 0;
    kolejka.push(mp(0,1));
    while(!kolejka.empty()){
        pair <ll, ll> parka = kolejka.top();
        kolejka.pop();
        int vb = parka.second;
        if(koszt[vb] == -parka.first){
            koszt[vb] = -parka.first;
            for(auto p:g[vb]){
                if(koszt[vb]+p.second < koszt[p.first] && drogowskazy[p.first]!=vb){
                    koszt[p.first] = koszt[vb] + p.second;
                    kolejka.push(mp(-koszt[vb] - p.second, p.first));
                }
            }
        }
    }
}
void wypisz_koszt(){
    for(int i=0; i<n; i++){
        cout<<i<<". "<<koszt[i]<<endl;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>a>>b>>d;
        g[a].pb(mp(b,d));
        g[b].pb(mp(a,d));
    }
    for(int i=0; i<n; i++){
        koszt[i] = infi;
        drogowskazy[i] = infi;
    }
    dijkstra();
    for(int i=0; i<n; i++){
        for(auto d:g[i]){
            if(koszt[i] == koszt[d.first] + d.second)
                drogowskazy[i] = d.first;
        }
    }
    deb{
        wypisz_koszt();
    }
    for(int i=0; i<n; i++) koszt[i] = infi;
    dijkstra();
    deb{
        cout<<endl<<endl<<"Dijkstra2\n";
        wypisz_koszt();
    }
    if(koszt[0] == infi){
        cout<<"impossible";
        return 0;
    }
    for(int i=0; i<n; i++){
        for(auto d:g[i]){
            if(koszt[i] == koszt[d.first] + d.second)
                drogowskazy2[i] = d.first;
        }
    }
    int v = 0;
    vector <int> path;
    path.pb(0);
    while(v!=1){
        v = drogowskazy2[v];
        path.pb(v);
    }
    cout<<path.sz<<"\n";
    for(auto p:path) cout<<p<<" ";
    return 0;
}
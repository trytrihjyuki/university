#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 100;
const ll inf = 1e18;
ll n,k,u,v,w,suma,ans=inf;
ll d[maxn];
ll visited[maxn];
priority_queue <ll> kolejka;
vector < pair <ll, ll > > g[maxn];
ll dfs(ll vb, ll master){ //
    visited[vb] = master;
    ll kanal_ludzie_vb = 0;
    for(auto para:g[vb]){
        if(visited[para.first] != master){
            ll kanal_ludzie = dfs(para.first, master);
            kanal_ludzie_vb+=kanal_ludzie;
            suma+=kanal_ludzie*para.second;
            kolejka.push(kanal_ludzie*para.second);
        }
    }
    return kanal_ludzie_vb + d[vb];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(ll i=1; i<=n; i++)
        cin>>d[i];
    for(ll i=0; i<n-1; i++){
        cin>>u>>v>>w;
        g[u].pb(mp(v,w));
        g[v].pb(mp(u,w));
    }
    for(ll i=1; i<=n; i++){
        suma = 0;
        dfs(i,i);
        for(ll j=0; j<k && !kolejka.empty(); j++){
            suma-=kolejka.top();
            kolejka.pop();
        }
        while(!kolejka.empty())
            kolejka.pop();
        ans = min(suma, ans);
    }
    cout<<ans;
 
    return 0;
}
/*
0. Dla każdego n:
1. Liczymy DFS-em ilosc ludzi przechodzących przez kanały * koszt kanału
2. Wybieramy K najdroższych kanałów i usuwamy 
 
/*
5 3
4 5 7 2 6
1 2 4
2 3 5
4 2 3
5 3 2
*/
/*
5 3
8 5 1 8 7
1 3 8
2 3 9
3 5 7
3 4 8
*/


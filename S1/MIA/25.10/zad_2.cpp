#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e5+100;
int a,b,n;
struct node
{
    int node;
    bool zmiana_now;
    bool zmiana_next;
};
bool goal[maxn], init[maxn],visited[maxn];
vector <int> g[maxn],ans;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1; i<n; i++){
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    g[0].pb(1);
    for(int i=1; i<=n; i++) cin>>init[i];
    for(int i=1; i<=n; i++) cin>>goal[i];
    queue <node> kolejka;
    node xd;
    xd.node = 0;
    xd.zmiana_now = 0;
    xd.zmiana_next = 0;
    kolejka.push(xd);
    while(!kolejka.empty()){
        node vb = kolejka.front();
        bool zmiana_w_wnuku = vb.zmiana_now;
        kolejka.pop();
        visited[vb.node] = 1;
        if(vb.zmiana_now) //czy przodkowie mnie zmieniaja
            init[vb.node] = !init[vb.node];
        if(goal[vb.node]^init[vb.node]){ //czy ja sie musze zmieniac
            zmiana_w_wnuku = !vb.zmiana_now;
            ans.pb(vb.node);
        }
        for(auto u:g[vb.node]){
            if(!visited[u]){
                node syn;
                syn.node = u;
                syn.zmiana_now = vb.zmiana_next;
                syn.zmiana_next = zmiana_w_wnuku;
                kolejka.push(syn);
            }
        }
    }
    cout<<ans.sz<<"\n";
    for(auto u:ans) cout<<u<<"\n";
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e5 + 10;
int n, ans,a,m,b;
int tab[maxn];
bool cats[maxn];
vector <int> g[maxn];
int cats_to_me[maxn];
bool visited[maxn];
bool slabe[maxn];
void dfs(int vb, int cats_here){
    visited[vb] = 1;
    cats_to_me[vb] = cats_here;
    if(cats[vb]) cats_to_me[vb]++;
    else cats_to_me[vb] = 0;
    deb cout<<"jestem w "<<vb<<" "<<cats_to_me[vb]<<endl;
    if(cats_to_me[vb] > m) slabe[vb] = 1;
    for(auto u:g[vb]){
        if(!visited[u]){
            if(slabe[vb]) slabe[u] = 1;
            dfs(u, cats_to_me[vb]);
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>a;
        if(a) cats[i] = 1;
    }
    for(int i=1; i<n; i++){
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1,0);
    for(int i=2; i<=n; i++){
        deb{
            cout<<i<<"\n";
            if(g[i].sz == 1){
                cout<<"jestem lisciem\n";
                cout<<"ile kotow do mnie: "<<cats_to_me[i]<<endl;
            }
        }
        if(g[i].sz == 1 && (!slabe[i])) ans++;
    }
    
    cout<<ans;

    return 0;
}
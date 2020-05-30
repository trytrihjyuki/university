#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll zeroo = 1800;
const ll maxn = zeroo*2;
const ll mod = 1000000007;
const ll infi = 1000000007;
int n,m,a,b,c,q;
vector <int> g[120][120];
bool colors[1000];
bool visited[1000];
void czysc(){
    for(int i=0; i<150; i++) visited[i] = 0;
}
bool czy_moge(int vb, int docelowy, int uniwersum){
    visited[vb] = 1;
    if(vb == docelowy) return true;
    bool ans = 0;
    for(int i=0; i<g[uniwersum][vb].sz; i++){
        if(!visited[g[uniwersum][vb][i]])
            ans = ans || czy_moge(g[uniwersum][vb][i],docelowy,uniwersum);
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>a>>b>>c;
        g[c][a].pb(b);
        g[c][b].pb(a);
        colors[c] = 1;
    }
    cin>>q;
    for(int i=0; i<q; i++){
        int odp = 0;
        cin>>a>>b;
        for(int col=0; col<=100; col++){
            if(colors[col]){
                if(czy_moge(a,b,col)) odp++;
                czysc();
            }
        }
        cout<<odp<<"\n";
    }
    return 0;
}
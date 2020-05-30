#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const int zeroo = 1800;
const ll maxn = zeroo*2;
const ll mod = 1000000007;
const ll infi = 1000000007;
int n,m,a,b;
vector <int> g[100];
int najblizsze[100];
int sciezki[100];
string s;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    queue <int> kolejka;
    kolejka.push(n);
    while(!kolejka.empty()){
        int vb = kolejka.front();
        kolejka.pop();
        for(int i=0; i<g[vb].sz; i++){
            if(!najblizsze[g[vb][i]] && g[vb][i]!=n){
                najblizsze[g[vb][i]] = najblizsze[vb] + 1;
                kolejka.push(g[vb][i]);
            }
        }
    }
    deb{
        cout<<"najblizsze[]:\n";
        for(int i=1; i<=n; i++) cout<<"najlizsze["<<i<<"]: "<<najblizsze[i]<<endl;
    }
    kolejka.push(1);
    int paths = 0;
    while(!kolejka.empty()){
        int vb = kolejka.front();
        kolejka.pop();
        for(int i=0; i<g[vb].sz; i++){
            if(najblizsze[g[vb][i]] = najblizsze[vb] - 1){
                sciezki
                kolejka.push(g[vb][i]);
            }
        }
    }
    return 0;
}
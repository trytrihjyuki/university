#include <bits/stdc++.h>
using namespace std;
#define sz size()
#define pb push_back
typedef long long ll;
const int maxn = 400010;
const bool debug1 = 0;
const bool debug2 = 0;
#define deb2 if(debug2)
#define deb1 if(debug1)


vector <int> g[maxn];
ll ans,n,m,a,b;
int poddrzewo[maxn];
bool visited[maxn];
void dfs(int vb){
    visited[vb] = 1;
    poddrzewo[vb]++;
    ll wywalam = 0;
    for(auto u:g[vb]){
        if(!visited[u]){
            dfs(u);
            wywalam+=poddrzewo[u]*poddrzewo[vb]; //wszystkie ktorych lca jest vb
            poddrzewo[vb]+=poddrzewo[u];
        }
    }
    ans-=wywalam*wywalam; // wszystkie pary przechodzace obie przez vb PRZYPADEK 1
    ans-=2*wywalam*poddrzewo[vb]*(n-poddrzewo[vb]); // wszystykie poza drzewem-poddrzewo oraz lca - vb PRZYPADEK 2
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1; i<n; i++){
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    ans=(n*(n-1)/2);
    ans*=ans;
    //wszystkie mozliwe pary par
    dfs(1);
    cout<<ans;
    return 0;
}
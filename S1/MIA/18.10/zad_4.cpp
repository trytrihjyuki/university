#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e5 + 2;
const ll k = 17;

int n,m,a,b,czas;
int ancestor[maxn][k], depth[maxn], ans[maxn], pre[maxn], post[maxn];
bool visited[maxn],bfs_visited[maxn];
int suma_podrzewo[maxn],roznica[maxn];
vector < pair <int, int > > edges;
vector <int> g[maxn];
void dfs(int vb){
    pre[vb] = czas++;
    visited[vb] = 1;
    for(auto u:g[vb]){
        if(!visited[u]){
            depth[u] = depth[vb] + 1;
            ancestor[u][0] = vb;
            dfs(u);
        }
    }
    post[vb] = czas++;
}
int dp(int vb){
    int v = 0;
    for(auto u:g[vb]){
        if(u!=ancestor[vb][0]){
            suma_podrzewo[vb]+=dp(u);
        }
    }
    suma_podrzewo[vb] += roznica[vb];
    return suma_podrzewo[vb];
}
void make_ancestor(){
    for(int i=1; i<k; i++){
        for(int j=1; j<=n; j++)
            ancestor[j][i] = ancestor[ancestor[j][i-1]][i-1];
    }
}
int lca(int a, int b){
    if(depth[a] > depth[b]) swap(a,b);
    for(int i=k-1; i>=0; i--){ //czy trzeba 20 -> 1
        if(depth[ancestor[b][i]] >= depth[a]) b = ancestor[b][i];
    }
    if(a==b) return a;
    for(int i=k-1; i>=0; i--){ //to samo pytanie?
        if(ancestor[a][i]!=ancestor[b][i]){
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1; i<n; i++){
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
        edges.pb(mp(a,b));
    }
    dfs(1);
    ancestor[1][0] = 1;
    make_ancestor();
    cin>>m;
    for(int i=0; i<m; i++){
        cin>>a>>b;
        roznica[a]++;
        roznica[b]++;
        roznica[lca(a,b)]-=2;
    }
    dp(1);
    for(auto par:edges){
        if(ancestor[par.first][0] == par.second)
            cout<<suma_podrzewo[par.first]<<" ";
        else
            cout<<suma_podrzewo[par.second]<<" ";
    }
    return 0;
}
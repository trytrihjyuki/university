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
int n,m,a,b,maksymalny,maksymalny_ind;
bool visited_mktree[maxn],low_visited[maxn],visted_dfs2[maxn],most[maxn];
int obroc[maxn];
int low[maxn], depth[maxn],/* opcjonalnie */ojciec[maxn];
vector <pair <int, int> > edges;
vector < pair <int, int> > g[maxn];
vector <int> drzewo[maxn];
vector <int> wsteczne[maxn];
stack <int> stos;
void mk_tree(int vb){
    visited_mktree[vb] = 1;
    for(auto u:g[vb]){
        if(!visited_mktree[u.first]){
            ojciec[u.first] = vb;
            drzewo[vb].pb(u.first);
            mk_tree(u.first);
        }
        else{
            if(u.first!=ojciec[vb]) wsteczne[vb].pb(u.first);
        }
        
    }
}
void cnt_low(int x)
{
    low_visited[x] = true;
    low[x] = depth[x];
    stos.push(x);
    for(int i = 0; i<(int)drzewo[x].size(); i++){ ///na wektorze drzewo trzymamy liste sasiedztwa drzewa rozpinajacego DFS
        if(!low_visited[drzewo[x][i]])
        {
            depth[drzewo[x][i]] = depth[x] + 1;
            cnt_low(drzewo[x][i]);
            low[x] = min(low[x], low[drzewo[x][i]]);
        }
    }
    for(int i = 0; i<(int)wsteczne[x].size(); i++) ///na wektorze krawedzie[x] trzymamy krawedzie wsteczne wychace z x
        low[x] = min(low[x], depth[wsteczne[x][i]]);
    
    if(low[x] == depth[x]){
        int v = 0;
        int rozmiar = 0;
        while(v!=x)
        {
            v = stos.top();
            stos.pop();
            rozmiar++;
            
        }
        if(rozmiar>maksymalny)
        {
            maksymalny = rozmiar;
            maksymalny_ind = x;
        }
    }
}
void dfs_2(int vb){
    visted_dfs2[vb] = 1;
    // cout<<"[START] w "<<vb<<endl;
    for(auto u:g[vb]){
        //deb2 cout<<"    Jestem w "<<vb<<" "<<u.first<<" "<<visted_dfs2[u.first]<<" "<<most[u.first]<<" "<<most[vb]<<endl;
        //deb2 cout<<"test "<<edges[u.second].first<<" "<<edges[u.second].second<<endl;
        if(!visted_dfs2[u.first]){
            //deb2 cout<<"obracam krawedz "<<edges[u.second].first<<" "<<edges[u.second].second<<endl;
            if(edges[u.second].first==vb&&edges[u.second].second==u.first) obroc[u.second] = 2;
            else obroc[u.second] = 1;
            dfs_2(u.first);
        }
        else{
            if(edges[u.second].first==vb&&edges[u.second].second==u.first) obroc[u.second] = 1;
            else obroc[u.second] = 2;
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1; i<=n; i++) low[i] = -maxn;
    edges.pb({0,0});
    for(int i=1; i<=m; i++){
        cin>>a>>b;
        g[a].pb({b,i});
        g[b].pb({a,i});
        edges.pb({a,b});
    }
    mk_tree(1);
    cnt_low(1);
    for(int i=1; i<=n; i++){
        if(low[i] == depth[i]){
            deb2 cout<<i<<" oraz "<<ojciec[i]<<" tworza most\n";
            most[i] = 1;
            most[ojciec[i]] = 1;
        }
    }
    deb1{
        cout<<"Wypisuje drzewo_dfs: \n";
        for(int i=1; i<=n; i++){
            cout<<i<<": ";
            for(auto u:drzewo[i]) cout<<u<<" ";
            cout<<endl;
        }
        cout<<"\n\nWypisuje krawedzie wsteczne: \n";
        for(int i=1; i<=n; i++){
            cout<<i<<": ";
            for(auto u:wsteczne[i]) cout<<u<<" ";
            cout<<endl;
        }
        cout<<"\n\nWypisuje depth: \n";
        for(int i=1; i<=n; i++)
            cout<<"depth["<<i<<"]: "<<depth[i]<<endl;
        cout<<"\n\n";
        cout<<"\n\nWypisuje LOW: \n";
        for(int i=1; i<=n; i++)
            cout<<"low["<<i<<"]: "<<low[i]<<endl;
        cout<<"\n\n";
        printf("Wypisuje mosty:\n");
        for(int i=1; i<=n; i++){
            if(low[i] == depth[i]){
                cout<<"Mostem jest krawedz "<<i<<" "<<ojciec[i]<<endl;
            }
        }
    }
    dfs_2(maksymalny_ind);
    cout<<maksymalny<<"\n";
    for(int i=1; i<edges.sz; i++){
        if(obroc[i]==2)
            cout<<edges[i].second<<" "<<edges[i].first<<"\n";
        else
            cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }

}
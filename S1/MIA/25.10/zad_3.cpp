#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e5+100;
const ll k = 25;
int n,a,b;
bool visited[maxn];
vector < int > g[maxn];
vector < pair <int, int> > ans;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int maksi = -maxn;
    int ind = -1;
    for(int i=1; i<n; i++){
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
        maksi = max(maksi,int(g[b].sz));
        maksi = max(maksi,int(g[a].sz));
        if(g[a].sz == maksi) ind = a;
        if(g[b].sz == maksi) ind = b;
    }
    //czy dupa
    for(int i=1; i<=n; i++){
        if(i!=ind&&g[i].sz>2){
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    //czy linia
    queue <int> kolejka;
    kolejka.push(ind);
    while(!kolejka.empty()){
        int vb = kolejka.front();
        kolejka.pop();
        visited[vb] = 1;
        bool flag = 0;
        for(auto u:g[vb]){
            if(!visited[u]){
                kolejka.push(u);
                flag = 1;
            }
        }
        if(!flag){
            ans.pb(mp(ind,vb));
        }
    }
    cout<<ans.sz<<"\n";
    for(auto u:ans){
        cout<<u.first<<" "<<u.second<<"\n";
    }
    return 0;
}
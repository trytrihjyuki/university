#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 2 * 1e6 + 10;
const int infi = -1e3;
int n,k;
bool dang[maxn];
string s;
vector <int> g[maxn];
/*
7 3
---X--X
-X--XX-


6 2
--X-X-
X--XX-

*/
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    cin>>s;
    for(int i=1; i<=n; i++){
        if(s[i-1] ==  'X') dang[i] = 1;
    }
    cin>>s;
    for(int i=1; i<=n; i++){
        if(s[i-1] ==  'X') dang[n+i] = 1;
    }
    for(int i=1; i<=n; i++){
        g[i].pb(i-1);
        g[i].pb(i+1);
        g[n+i].pb(n+i+1);
        if(i>=1) g[n+i].pb(n+i-1);
        if(i+k <= n){
            g[i].pb(n+i+k);
            g[n+i].pb(i+k);
        }
    }
    queue < pair <int, int> > kolejka;
    kolejka.push({1,1});
    while(!kolejka.empty()){
        int vb = (kolejka.front()).first;
        int czas = (kolejka.front()).second;
        deb cout<<vb<<" czas: "<<czas<<endl;
        if(2*n-k+1 <= vb && vb <= 2*n){
            cout<<"YES";
            return 0;
        }
        if(n-k+1 <= vb && vb <= n){
            cout<<"YES";
            return 0;
        }
        kolejka.pop();
        for(auto u:g[vb]){
            if(!dang[u]){
                dang[u] = 1;
                if(u>n){
                    if(u-n > czas){
                        deb cout<<vb<<" -> "<<u<<endl;
                        kolejka.push({u,czas+1});
                    }
                }
                else{
                    if(u > czas){
                        deb cout<<vb<<" -> "<<u<<endl;
                        kolejka.push({u,czas+1});
                    }
                }
            }
        }
    }
    cout<<"NO";
    return 0;
}
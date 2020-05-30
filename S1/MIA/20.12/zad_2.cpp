#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll zeroo = 1800;
const ll maxn = zeroo*2;
const ll mod = 1000000007;
const ll infi = 1000000007;
ll n,m,a,b;
long double maks;
ll odleglosc[120][120];
ll rozne[120][120];
string s;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(ll i=0; i<120; i++){
        for(ll j=0; j<120; j++)
            odleglosc[i][j] = infi;
    }
    for(ll i=0; i<m; i++){
        cin>>a>>b;
        odleglosc[a][b] = 1;
        odleglosc[b][a] = 1;
        rozne[a][b] = 1;
        rozne[b][a] = 1;
    }
    for(ll i=1; i<=n; i++){
        for(ll j=1; j<=n; j++){
            for(ll k=1; k<=n; k++){
                if(odleglosc[j][i]+odleglosc[i][k] <= odleglosc[j][k]){ 
                    if(odleglosc[j][i]+odleglosc[i][k] < odleglosc[j][k])//oplaca sie przejsc przez ziomala
                        rozne[j][k] = 0;
                    odleglosc[j][k] = odleglosc[j][i] + odleglosc[i][k];
                    rozne[j][k]+=rozne[j][i]*rozne[i][k];
                }
            }
        }
    }
    deb{
        for(ll i=1; i<=n; i++){
            for(ll j=1; j<=n; j++){
                cout<<"rozne["<<i<<"]["<<j<<"]: "<<rozne[i][j]<<endl;
            }
        }
    }
    maks = rozne[1][n];
    for(ll i=0; i<n; i++){
        if(odleglosc[1][i]+odleglosc[i][n] == odleglosc[1][n]){
            maks = max(maks, 2*(long double)rozne[1][i]*rozne[i][n]);
        }
    }
    printf("%0.9Lf\n",maks/rozne[1][n]);
    return 0;
}
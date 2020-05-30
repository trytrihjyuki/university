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
int n,m,k;
string s,t;
int dp[maxn][3*maxn];
int ans = 0;
int smak[maxn];
int kalorie[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    for(int i=1; i<=n; i++)
        cin>>smak[i];
    for(int i=1; i<=n; i++){
        cin>>kalorie[i];
        kalorie[i]*=k;
    }
    for(int i=0; i<maxn; i++){
        for(int j=0; j<3*maxn; j++)
            dp[i][j] = -infi;
    }
    dp[0][zeroo] = 0;
    for(int i=1; i<=n; i++){
        for(int suma=0; suma<maxn; suma++){
            dp[i][suma] = max(dp[i-1][suma],dp[i-1][suma+kalorie[i]-smak[i]] + smak[i]);
        }
    }
    if(dp[n][zeroo]<=0) cout<<-1;
    else cout<<dp[n][zeroo];
    return 0;
}
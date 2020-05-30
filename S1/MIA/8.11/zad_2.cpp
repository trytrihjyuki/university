#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 5*1e3 + 100;
const ll mod = 1000000007;
const ll infi = 1e18;
ll n,m,k,a,ans = 0;
ll dp[maxn][maxn];
ll input[maxn],sumy[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1; i<=n; i++) cin>>input[i];
    for(int i=1; i<=n; i++) sumy[i] = sumy[i-1] + input[i];
    for(int i=1; i<=n; i++){
        for(int j=1; j<=k; j++){
            dp[i][j] = dp[i-1][j];
            if(i-m>=0) dp[i][j] = max(dp[i][j],dp[i-m][j-1]+sumy[i]-sumy[i-m]);
        }
    }
    cout<<dp[n][k];

    return 0;
}

/*
20 5 3
                                         15
96 46 67 36 59 95 88 43 92 58 1 31 69 35 36 77 56 27 3 23
*/
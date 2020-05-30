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
int n,m;
string s,t;
int dp[maxn][maxn];
int ans = 0;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>s>>t;
    for(int i=0; i<s.sz; i++){
        for(int j=0; j<t.sz; j++){
            if(j>0) dp[i][j] = dp[i][j-1]; //nie biore jtego elementu
            if(s[i]==t[j]&&i*j>0) dp[i][j] = (dp[i][j] + dp[i-1][j-1] + 1)%mod; //biore jty element
            if(s[i]==t[j]&&i*j==0) dp[i][j] = (dp[i][j] + 1)%mod;
            deb cout<<"dp["<<i<<"]["<<j<<"]: "<<dp[i][j]<<endl;
        }
    }
    for(int i=0; i<s.sz; i++) ans = (ans + dp[i][t.sz-1])%mod;
    cout<<ans;
    return 0;
}
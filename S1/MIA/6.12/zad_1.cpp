#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1005;
const ll k = 25;
int n,a,b,m;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<(n%m); i++) cout<<n/m+1<<" ";
    for(int i=0; i<m-(n%m); i++) cout<<n/m<<" ";
    return 0;
}
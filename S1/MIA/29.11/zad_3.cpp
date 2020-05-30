#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e6 + 100;
const ll k = 17;
const ll mod = 1000000007;
int n,m,a,np,p;
int suma[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int ans = 0;
    for(int i=0; i<n; i++){
        cin>>a;
        if(a%2) np++;
        else p++; 
        if(p%)2 cout<<"1\n";
        else cout<<"2\n";
    }
    return 0;
}
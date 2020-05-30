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
int np,p;
string s;
int ilosc[1000];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    for(int i=0; i<s.sz; i++) ilosc[s[i]]++;
    for(int i=0; i<s.sz; i++){
        if(ilosc[s[i]]%2==0) p++;
        else np++;
    }
    if((np-1)%2==0||np==0) cout<<"First";
    else cout<<"Second";
    return 0;
}
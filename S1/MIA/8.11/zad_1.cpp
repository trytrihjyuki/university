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
int n,m;
int suma[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int konczace_0 = 0, konczace_1 = 0;
    konczace_0++; //ciag 01010101...
    for(int i=1; i<n; i++){
        if(i%2) konczace_1+=konczace_0+1;
        else konczace_0+=konczace_1+1;
        konczace_0 = konczace_0 % mod;
        konczace_1 = konczace_1 % mod;
    }
    cout<<(konczace_1+konczace_0)%mod;
    return 0;
}
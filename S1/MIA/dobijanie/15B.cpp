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
int n,t,c,ans;

void bin(unsigned n) 
{ 
    unsigned i; 
    for (i = 1 << 10; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a,b,bigB;
    cin>>a>>b;
    for (int j = 0; j < 63; j++){
        bigB = (ll)pow(2, j) - 1;
        deb {printf("baza: dec:%lld\nbin:",bigB);bin(bigB);printf("\n");}
        for(int i = 0; i < j-1; i++)
        {
            // cout<<bigB<<endl;
            bigB = bigB ^ (ll)(pow(2,i));
            if (a<=bigB && b>=bigB) ans++;
            deb if (a<=bigB && b>=bigB) {printf("    GOODONE dec: %lld\n    bin: ",bigB);bin(bigB);printf("\n");}
            bigB = bigB ^ (ll)(pow(2,i));
        }
    }
    cout<<ans;
    return 0;
}
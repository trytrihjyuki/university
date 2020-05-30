#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1005;
const ll infi = 1000000000;
const ll k = 25;
int n,a,b,c,ans=1000;
string s;
int cards[100];
int translator[10000];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    translator['R']=0+5;
    translator['G']=1+5;
    translator['B']=2+5;
    translator['Y']=3+5;
    translator['W']=4+5;
    for(int i=0; i<n; i++){
        cin>>s;
        cards[i] = (1<<translator[s[0]]) + (1<<(s[1]-'1'));
    }
    for(int mask=0; mask<1<<10; mask++){
        bool flag = 0;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if(cards[i]!=cards[j] && (!(mask&(cards[i]^cards[j])))) flag = 1;
            }
        }
        if(!flag){
            int bits = 0;
            for(int b=0; b<10; b++) bits+=(bool)(mask&(1<<b));
            ans = min(ans,bits);
        }
    }
    cout<<ans;
    return 0;
}
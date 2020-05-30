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
int n,s,a;
vector <int> piles[105];
int ans_1,ans_2;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>s;
        for(int j=0; j<s; j++){
            cin>>a;
            piles[i].pb(a);
        }
    }
    int karty_wziete = 0;
    for(int i=0; i<n; i++){
        //karty_wziete+=max(int(((piles[i].sz)/2)),0);
        for(int j=0; j<(piles[i].sz)/2; j++) ans_1+=piles[i][j];
        for(int j=piles[i].sz-1; (piles[i].sz+1)/2<=j; j--) ans_2+=piles[i][j];
    }
    vector <int> srodkowe;
    for(int i=0; i<n; i++){
        if(piles[i].sz % 2 == 1){
            srodkowe.pb(-piles[i][piles[i].sz/2]);
        }
    }
    //cout<<"karty_wziete: "<<karty_wziete<<endl;
    sort(srodkowe.begin(), srodkowe.end());
    for(int i=0; i<srodkowe.sz; i++){
        //cout<<i<<" "<<karty_wziete<<" "<<i%2<<" "<<karty_wziete%2<<endl;
        if(i%2==0) ans_1-=srodkowe[i];
        else ans_2-=srodkowe[i];

    }
    cout<<ans_1<<" "<<ans_2;
    return 0;
}
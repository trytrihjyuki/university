#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll zeroo = 1800;
const ll maxn = 1e6+190;
const ll mod = 1000000007;
const ll infi = 1000000007;
ll n,zz,zj,jj,jz;
string s,ans;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>zz>>zj>>jz>>jj;
    ll ilosc_j = 0, ilosc_z = 0;
    if(zz+zj+jz+jj == 0){
        cout<<"0";
        return 0;
    }
    for(ll i=0; i<maxn; i++){
        if((i*(i-1))/2 == jj) ilosc_j = i;
        if((i*(i-1))/2 == zz) ilosc_z = i;
    }
    //cout<<ilosc_j<<" "<<ilosc_j;
    ll wszystkie = 0;
    wszystkie = ilosc_j + ilosc_z;
    if(jj+zj+jz==0 && ilosc_z!=0){
        for(int i=0; i<ilosc_z; i++) cout<<0;
        return 0;
    }
    if(ilosc_j!=0 && zz+zj+jz==0){
        for(int i=0; i<ilosc_j; i++) cout<<1;
        return 0;
    }
    if((wszystkie*(wszystkie-1))/2 != jj+zz+zj+jz){
        cout<<"Impossible";
        return 0;
    }
    while(0<ilosc_z || 0<ilosc_j){
        if(zj>=ilosc_j){ //zeby sie zgadzaly 01 dopychańsko na maksa aż do limitu pózniej damy 0 w jednym dobrym miejscu miedzy jedynkami
            cout<<"0";
            zj-=ilosc_j;
            ilosc_z--;
        }
        else{
            cout<<"1";
            jz-=ilosc_z;
            ilosc_j--;
        }
    }
    return 0;
}
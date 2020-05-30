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
int n;
ll x,m;
int suma[maxn];
ll licz_xorka(int n){ 
    switch(n & 3){ 
    case 0: return n;
    case 1: return 1;
    case 2: return n + 1;
    case 3: return 0;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //int xd,xorek = 0,xorek_git = 0,xorek_2 = 0;
    //cin>>x>>m;
    ///*  Brute   */
    //for(int i=1; i<x+m; i++) xorek = xorek ^ i;
    //for(int i=1; i<x; i++) xorek_2 = xorek_2 ^ i;
    //for(int i=x; i<m+x; i++) xorek_git = xorek_git^i;
    //cout<<xorek<<"^"<<xorek_2<<"="<<(xorek^xorek_2)<<endl;
    //cout<<xorek_git<<endl;
    ///*  Ja  */
    //xorek = 0;
    //if((x+m-1)%2) xorek = 1; //wszystkie kamienie
    //else xorek = (x+m-1)+1;
    //xorek_2 = 0;
    //if(x==1) xorek_2 = 0;
    //else{
    //    if((x-1)%2) xorek_2 = 1;
    //    else xorek_2 = x;
    //}
    //xorek = xorek ^ xorek_2;
    //cout<<"ze wzurka: "<<xorek;
    cin>>n;
    int xorek_gigant = 0;
    for(int i=0; i<n; i++){
        cin>>x>>m;
        deb cout<<i<<":\n";
        int xorek, xorek_2;
        xorek = licz_xorka(x+m-1);
        xorek_2 = licz_xorka(x-1);
        deb cout<<"xorek: "<<xorek<<"\nxorek_2: "<<xorek_2;
        xorek = xorek ^ xorek_2;
        deb cout<<"\nxorek^xorek_2: "<<xorek<<endl<<endl;
        xorek_gigant = xorek_gigant ^ xorek;
    }
    if(xorek_gigant) cout<<"tolik";
    else cout<<"bolik";
    return 0;
}
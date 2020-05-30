#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
int n, ans,a;
int tab[maxn];
vector <int> v;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>a;
        v.pb(-a);
    }
    int ali = 0;
    int bob = 0;
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++){
        if(i%2) bob-=v[i];
        else ali-=v[i];
    }
    int ali2 = 0;
    int bob2 = 0;
    if(n>1) ali2-=v[1];
    bob2-=v[0];
    for(int i=2; i<n; i++){
        if(i%2) bob2-=v[i];
        else ali2-=v[i];
    }
    if(ali2>ali)
        cout<<ali2<<" "<<bob2;
    else
        cout<<ali<<" "<<bob;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
int n, ans;
int tab[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>tab[i];
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(tab[i] > tab[j]) ans++;
        }
    }
    cout<<ans;
    return 0;
}
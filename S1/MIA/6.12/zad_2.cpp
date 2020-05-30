#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll N = 101;
int n,m;
int k[N],f[N];
bool ans_tab[1000];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0; i<m; i++)
        cin>>k[i]>>f[i];
    vector <int> gitara_siema;
    for(int flats_in_floor=1; flats_in_floor<101; flats_in_floor++){
        bool flag = 0;
        for(int i=0; i<m; i++){
            if(k[i]>flats_in_floor*(f[i]-1) && k[i]<=flats_in_floor*f[i]){
                //git
            }
            else flag = 1;
        }
        if(!flag) gitara_siema.pb(flats_in_floor);
    }
    int licznik = 0;
    int ans = 0;
    for(int i=0; i<gitara_siema.sz; i++){
            if(n%gitara_siema[i]==0)
            {
                ans = n/gitara_siema[i];
                ans_tab[ans] = 1;
            }
            else{
                ans = n/gitara_siema[i] + 1; 
                ans_tab[ans] = 1;
            }
    }
    for(int i=0; i<1000; i++){
        if(ans_tab[i]){
            licznik++;
            ans = i;
        }
    }
    if(licznik!=1){
        cout<<-1;
        return 0;
    }
    cout<<ans;
    return 0;
}
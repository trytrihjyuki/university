#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 5*1e5+ 10;
ll n, elem;
bool jedynka;
unordered_set <ll> secik;
unordered_set <ll> aktualne1;
unordered_set <ll> aktualne2;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    aktualne1.clear();
    for(ll i=0; i<n; i++){
        cin>>elem;
        
        if(i%2) aktualne1.clear();
        else aktualne2.clear();

        if(i%2 /*&& !(find(aktualne2.begin(), aktualne2.end(), elem) != aktualne2.end())*/) aktualne2.insert(elem);
        if(i%2 == 0 /*&& !(find(aktualne1.begin(), aktualne1.end(), elem) != aktualne1.end())*/) aktualne1.insert(elem);

        if(i%2){
            for(auto d:aktualne2){
                ll gcdd = __gcd(d,elem);
                if(gcdd != 1){
                    deb cout<<"1) dodaje do seta: "<<d<<endl;
                    secik.insert(gcdd);
                    aktualne1.insert(gcdd);
                }
                else{
                    if(!jedynka){
                        secik.insert(1); 
                        jedynka = 1;
                    }
                }
            }
        }
        else{
            for(auto d:aktualne1){
                ll gcdd = __gcd(d,elem);
                if(gcdd != 1){
                    deb cout<<"2) dodaje do seta: "<<d<<endl;
                    secik.insert(gcdd);
                    aktualne2.insert(gcdd);
                }
                else{
                    if(!jedynka){
                        secik.insert(1);
                        jedynka = 1;
                    }
                }
            }
        }
    }
    cout<<secik.size();
    deb{
        cout<<endl;
        for(auto e:secik) cout<<e<<" ";
    }
    return 0;
}
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
ll n,a,b,c;
ll ans = 0;
int itek = 0;
ll cyfry[10];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    set <int> secior;
    for(ll k=1; k<=10; k++){
        for(ll mask=0; mask<(1<<(10)); mask++){
            for(int i=0; i<=9; i++){
                for(int j=0; j<=9; j++){
                    ll liczba = 0;
                    for(ll bit=1; bit<k; bit++){
                        if((1<<bit)&(mask)) liczba+=i;
                        else liczba+=j;
                        liczba*=10;
                    }
                    liczba/=10;
                    itek++;
                    if(liczba<=n) secior.insert(liczba);
                }
            }
        }
    }
    int wynik = secior.sz;
    wynik--;
    if(n==1000000000) wynik++;
    cout<<wynik;
    return 0;
}
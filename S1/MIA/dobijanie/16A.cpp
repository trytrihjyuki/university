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
int n,t,c;
int main(){
    vector <int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    vector <int> div;
    string response;
    for (auto prime: primes)
    {
        cout<<prime<<"\n";
        fflush(stdout);
        cin>>response;
        if(response == "yes") div.pb(prime);
        if(div.sz > 1)
        {
            cout<<"composite"<<"\n";
            fflush(stdout);
            return 0;
        }
    }
    if(div.sz == 0 || div[0] > 7)
    {
        cout<<"prime\n";
        fflush(stdout);
        return 0;
    }
    cout<<div[0]*div[0]<<"\n";
    fflush(stdout);
    cin>>response;
    if(response == "yes")
    {
        cout<<"composite"<<"\n";
        fflush(stdout);
        return 0;
    }
    else
    {
        cout<<"prime\n";
        fflush(stdout);
        return 0;
    }
}
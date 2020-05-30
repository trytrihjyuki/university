#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
ll t,n,m,x_1,x_2,y_1,y_2;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m>>x_1>>y_1>>x_2>>y_2;
        ll xp = n - max(x_1,x_2);
        ll xl = min(x_1,x_2) - 1;
        ll yg = min(y_1,y_2) - 1;
        ll yd = m - max(y_1, y_2);
        ll x_wspolny = (max(x_1,x_2) - xl) - (min(x_1,x_2) + xp) - 1; 
        ll y_wspolny = (max(y_1,y_2) - yg) - (min(y_1,y_2) + yd) - 1;
        if(x_wspolny > 0)
            x_wspolny = 0;
        if(y_wspolny > 0)
            y_wspolny = 0;
        
        deb{
            cout<<endl;
            cout<<"można iść maksymalnie w górę o: "<<yg<<endl;
            cout<<"można iść maksymalnie w dół o: "<<yd<<endl;
            cout<<"można iść maksymalnie w prawo o: "<<xp<<endl;
            cout<<"można iść maksymalnie w lewo o: "<<xl<<endl;
            cout<<endl<<"każdy z punktów zajmuje: "<<(m-max(y_1,y_2)+min(y_1,y_2))<<" x "<<(n-max(x_1,x_2)+min(x_1,x_2))<<" czyli "<<(m-max(y_1,y_2)+min(y_1,y_2))*(n-max(x_1,x_2)+min(x_1,x_2))<<endl;
            cout<<endl<<"część wspólna zajmuje "<<x_wspolny<<" x "<<y_wspolny<<" czyli "<<x_wspolny*y_wspolny<<endl;
        }
        cout<<n*m - (2*(m-max(y_1,y_2)+min(y_1,y_2))*(n-max(x_1,x_2)+min(x_1,x_2))) + x_wspolny*y_wspolny <<"\n";
 
    }
    return 0;
}
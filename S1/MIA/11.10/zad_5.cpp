#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e3 + 10;
const ld pii = 3.141592653589793238462643383279502884197;
ld  ax,ay,bx,by,r;
ld m,n;
int tab[maxn];
ld idz_srodkiem(ld x1, ld y1, ld x2, ld y2){
    if(x1==x2) return ((abs(y1-y2))/n)*r;
    else
        return ((y1+y2)/n)*r;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>m>>n>>r>>ax>>ay>>bx>>by;
    ld ans1 = 0.0;
    ans1 += (abs(ay-by)/n)*r;
    deb cout<<"ans1 "<<ans1<<endl;
    ans1+=ld((min(ay,by)/n)*r)*(ld(abs(ax-bx)/m))  * pii;
    ld ans2 = n-ay + by;
    ans1 = min(ans1, idz_srodkiem(ax,ay,bx,by));
    deb cout<<"ans2 "<<ans1<<endl;
    cout<<setprecision(12)<<ans1;
 
    return 0;
}
/*
6 5 2.0
1 3 4 2
*/
/*
9 7 3.0
1 5 9 5
*/
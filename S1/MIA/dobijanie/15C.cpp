ad#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 100005;
int n,m,a,b,c,q,k;
int ans1,ans2;
vector <int> answers[100];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    ans1 = ans2 = -1;
    for(int i = 0; i < n; i++)
    {
        int pot2 = 1;
        int id = 0; int sum = 0;
        for (int j = 0; j < k; j++)
        {
            cin>>b;
            id += pot2*b;
            pot2*=2;
            sum+=b;
        }
        
            answers[id].pb(1);
    }

    for (int i = 0; i < 100; i++)
    {

        for (int j = 0; j < 100; j++)
        {
            bool flag = 1;
            for (int bit = 0; bit < 4; bit++)
            {
                if ((1<<bit)&i && (1<<bit)&j) flag = 0;
            }
            if (flag && !answers[i].empty() && !answers[j].empty())
            {
                cout<<"YES";
                return 0;
            }
        }
    }
    cout<<"NO";

    return 0;
}
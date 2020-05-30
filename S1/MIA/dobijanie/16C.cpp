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
vector < int > g[maxn];

bool compare (int a, int b)
{
    printf("? %d %d\n",a,b);
    fflush(stdout);
    char response;
    cin>>response;
    return (response=='<');
}

int main(){
    int T;
    char response;
    cin>>T;

    while (T--)
    {
        cin>>n;
        int tab[n+1];
        for (int i = 1; i <= n; i++) tab[i] = i;
        pair<int*,int*> mnmx; 
        mnmx = minmax_element(tab+1, tab+1+n,compare);
        cout<<"! "<<*mnmx.first<<" "<<*mnmx.second<<"\n";
        fflush(stdout);
    }

    return 0;
}
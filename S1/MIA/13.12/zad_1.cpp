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
int n,a,b,m;
string s;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    sort(s.begin(), s.end());
    string s2 = "000000";
    for(int i = 0; i < s.sz; i++)
    {
        int it = i;
        int combo = 1;
        while (it+1 < s.sz && s[it] == s[it+1]){it++; combo++;}
        s2[i] = combo + '0';
        i = it;
    }
    sort(s2.begin(), s2.end());
    reverse(s2.begin(), s2.end());
    if (s2 == "600000") cout<<1<<"\n";
    if (s2 == "510000") cout<<1<<"\n";
    if (s2 == "420000") cout<<2<<"\n";
    if (s2 == "330000") cout<<2<<"\n";
    if (s2 == "411000") cout<<2<<"\n";
    if (s2 == "321000") cout<<3<<"\n";
    if (s2 == "311100") cout<<5<<"\n";
    if (s2 == "222000") cout<<6<<"\n";
    if (s2 == "221100") cout<<8<<"\n";
    if (s2 == "211110") cout<<15<<"\n";
    if (s2 == "111111") cout<<30<<"\n";

    return 0;
}
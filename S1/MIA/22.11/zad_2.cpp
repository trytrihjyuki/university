#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const int zeroo = 1800;
const ll maxn = 1e5+100;
const ll mod = 1000000007;
const ll infi = 1000000007;
int n;
string s;
string ans;
int najblizszy_ziomal[maxn][200];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    for(int i=0; i<maxn; i++){
        for(int j=0; j<200; j++)
            najblizszy_ziomal[i][j] = infi;
    }
    for(int i=s.sz-1; i>=0; i--){
        deb cout<<"najblizszy_ziomal["<<i<<"]["<<s[i]<<"]: "<<najblizszy_ziomal[i][s[i]]<<endl;
        deb cout<<"najblizszy_ziomal["<<i<<"]["<<char(s[i]+1)<<"]: "<<najblizszy_ziomal[i][s[i]+1]<<endl;
        deb cout<<"najblizszy_ziomal["<<i<<"]["<<char(s[i]+2)<<"]: "<<najblizszy_ziomal[i][s[i]+2]<<endl<<endl;
        for(int j='a'; j<='z'; j++){
            najblizszy_ziomal[i][j] = najblizszy_ziomal[i+1][j];
        }
        najblizszy_ziomal[i][int(s[i])] = i;
        deb cout<<"najblizszy_ziomal["<<i<<"]["<<s[i]<<"]: "<<najblizszy_ziomal[i][s[i]]<<endl;
        deb cout<<"najblizszy_ziomal["<<i<<"]["<<char(s[i]+1)<<"]: "<<najblizszy_ziomal[i][s[i]+1]<<endl;
        deb cout<<"najblizszy_ziomal["<<i<<"]["<<char(s[i]+2)<<"]: "<<najblizszy_ziomal[i][s[i]+2]<<endl<<endl<<endl<<endl;
    }
    for(int i=0; i<s.sz; i++){
        for(int j='z'; j>='a'; j--){
            deb cerr<<char(j)<<" "<<i<<" "<<s[i]<<" "<<najblizszy_ziomal[i][j]<<endl;
            if(najblizszy_ziomal[i][j]!=infi){
                deb cout<<"dodaje do ansa  "<<char(j)<<endl;
                ans+=char(j);
                i=najblizszy_ziomal[i][j];
                j=0;
            }
        }
    }
    cout<<ans;
    return 0;
}
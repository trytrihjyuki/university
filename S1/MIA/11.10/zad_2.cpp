#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz size()
const ll maxn = 1e3 + 100;
int n;
string s;
bool visited[maxn], flag, wygrywa[maxn][maxn];
vector <int> g[maxn];
vector <int> ans;
void dfs(int vb){
    if(ans.sz==n-1){
        flag = 1;
        return;
    }
    for(int i=0; i<n; i++){
        if(!visited[i] && wygrywa[vb][i]){
            visited[i] = 1;
            ans.pb(i);
            dfs(i);
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>s;
        for(int j=0; j<s.sz; j++){
            if(s[j] == '1')
                wygrywa[i][j] = 1;
        }
    }

    visited[0] = 1;
    dfs(0);

    if(!flag){
        cout<<"impossible";
        return 0;
    }
    for(int i=ans.sz-1; i>=0; i--) cout<<ans[i]<<" ";
    cout<<0;
    return 0;
}
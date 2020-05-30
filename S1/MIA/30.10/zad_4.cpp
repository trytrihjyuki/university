#include <bits/stdc++.h>
using namespace std;
#define sz size()
#define pb push_back
const int maxn = 2*(1e5)+100;
const int sizet = 1<<19;
const bool debug1 = 0;
const bool debug2 = 1;
#define deb2 if(debug2)
#define deb1 if(debug1)
int n,t,p;
vector <int> ans[maxn];
int tail[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>t;
        p = upper_bound(tail, tail + n, t, greater<int>()) - tail; //najwiekszy mniejszy 
        ans[p].pb(t);
        tail[p] = t;
    }
    int i = 0;
    while(tail[i]){ 
        for(auto odp:ans[i])
            cout<<odp<<" ";
        cout<<"\n";
        i++;
    }
    return 0;
}


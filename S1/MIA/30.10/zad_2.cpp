#include <bits/stdc++.h>
using namespace std;
#define sz size()
#define pb push_back
typedef long long ll;
const int maxn = 400010;
const int sizet = 1<<17;
const bool debug1 = 0;
const bool debug2 = 0;
#define deb2 if(debug2)
#define deb1 if(debug1)
int a,n,m,p,b;
int tree[(1<<18)];
void change(int ind, int v){
    //cout<<"Jestem w \n "<<ind<<endl;
    ind+=sizet;
    tree[ind] = v;
    int itek = 0;
    ind/=2;
    while(ind){
        //cout<<"Jestem w "<<ind;
        //cout<<"  drzewo ode mnie"<<tree[ind]<<endl;
        if(itek%2) tree[ind] = tree[2*ind] ^ tree[2*ind+1];
        else tree[ind] = tree[2*ind] | tree[2*ind+1];
        //cout<<"  po updacie "<<tree[ind]<<endl;
        ind/=2;
        itek++;
    }
    if(itek%2) tree[ind] = tree[2*ind]^tree[2*ind+1];
    else tree[ind] = tree[2*ind]|tree[2*ind+1];

}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0; i<(1<<n); i++){
        cin>>a;
        change(i,a);
    }
    for(int i=0; i<m; i++){
        cin>>p>>b;
        p--;
        change(p,b);
        cout<<tree[1]<<"\n";
    }
    return 0;
}
/*
2 1
1 6 3 5
1 4
*/
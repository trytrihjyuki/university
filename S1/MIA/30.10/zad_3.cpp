#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1e5+100;
const ll k = 25;
const int sizet = 131072;
int tree[2*sizet][30];
void add(int a, int v, int ind){
    a+=sizet;
    tree[a][ind]+=v;
    a/=2;
    while(a){
        tree[a][ind]=tree[2*a][ind]+tree[2*a+1][ind];
        a/=2;
    }
    tree[0][ind]+=v;
}
ll sumka(int a, int b, int ind){
    int sumka = 0;
    a+=sizet;
    b+=sizet;
    // if(a==b) return tree[a][ind];
    // sumka+=tree[a][ind];
    // sumka+=tree[b][ind];
    // a/=2;
    // b/=2;
    while(a<=b){
        if(a&1){
            sumka+=tree[a][ind];
            a++;
        }
        if(!(b&1)){
            sumka+=tree[b][ind];
            b--;
        }
        a/=2;
        b/=2;
    }
    if(a==b) sumka+=tree[a][ind];
    return sumka;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    int q;
    for(int i=0; i<s.sz; i++) add(i,1,(s[i]-97));
    cin>>q;
    int a,b,c;
    char z;
    for(int i=0; i<q; i++){
        cin>>a;
        if(a==1){
            cin>>b>>z;
            add(b-1,1,(z-97));
            add(b-1,-1,(s[b-1]-97));
            s[b-1]=z;
        }
        else{
            cin>>b>>c;
            b--;
            c--;
            int anss = 0;
            for(int j=0; j<26; j++){
                if(sumka(b,c,j)) anss++;
            }
            cout<<anss<<"\n";
        }
    }
    return 0;
}
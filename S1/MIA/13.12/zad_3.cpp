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
int n,a,b,m,rozne;
int licz[500];
string s;
bool jest(int a){
    for(int i=0; i<500; i++){
        if(licz[i] == a) return 1;
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    for(int i=0; i<s.sz; i++){
        if(!licz[s[i]]) rozne++;
        licz[s[i]]++;
    }
    int wynik = 1;
    for(int i=0; i<500; i++){
        if(licz[i] == 2) wynik*=2;
    }
    if(rozne == 1){
        cout<<1;
        return 0;
    }
    if(rozne == 2){
        if(jest(4)){ // 4 2
            cout<<2;
            return 0;
        }
        if(jest(3)){ // 3 3
            cout<<6;
            return 0;
        }
        if(jest(5)){ // 5 1
            cout<<1;
            return 0;
        }
    }
    if(rozne == 3){
        if(jest(4)){ // 4 1 1
            cout<<2;
            return 0;
        }
        if(jest(3)){ //3 2 1
            cout<<3;
            return 0;
        }
        if(jest(2)){ // 2 2 2
            cout<<3;
            return 0;
        }
    }
    if(rozne == 4){
        if(jest(3)){ // 3 1 1 1
            cout<<2;
            return 0;
        }
        if(jest(2)){ // 2 2 1 1
            cout<<3; //???????
            return 0;
        }
    }
    if(rozne == 5){
        cout<<2;
        return 0;
    }
    if(rozne == 6){
        cout<<30;
        return 0;
    }
    return 0;
}
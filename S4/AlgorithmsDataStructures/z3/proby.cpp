#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll MAXMASK_SQ = (1<<9) - 1;
const ll MAXMASK_L = (1<<5) - 1; 
const ll MAXN = 2000;
const ll INF = int(1e6) + 10;

int main() {
    int m1OG = 24;
    for (int i=0; i<3; i++){
        int m1 = (m1OG>>i);
        int m2 = (m1OG>>i);
        int m3 = (m1OG>>i);
        cout << "1: "<<m1<<endl;
        m1 = m1 & ((1<<3)-1);
        m2 = m2 & ((1<<3)-1);
        m3 = m3 & ((1<<3)-1);
        cout << "2: "<<m1<<endl;
        m2 = (m2<<3);
        m3 = (m3<<6);

        cout << "3: "<<m1<<" "<<m2<<" "<<m3<<endl<<endl;;
        if (m1+m2+m3 == 0) return false;
    }
    return 0;
}
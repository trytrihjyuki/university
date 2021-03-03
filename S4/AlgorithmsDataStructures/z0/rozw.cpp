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



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a,b;
    cin >> a >> b;
    if (a > b) swap(a,b);

    for (int i = a; i <= b; i++) cout << i << '\n';

    return 0;
}
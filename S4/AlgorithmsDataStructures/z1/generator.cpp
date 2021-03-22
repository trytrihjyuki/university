#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector <string> dictionary;

const bool debug = 1;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const int maxn = (int)10 + 1;
const int maxd = (int)15 + 1;
int used[maxd];
int main(int argc, char** argv){
    srand(atoi(argv[1]));
    int m = rand()%((int)maxn+1);
    cout << m << endl;
    for (int i = 0; i < m; i++)
    {
        int d = rand()%maxd+1;
        while (used[d]) d = rand()%maxd+1;
        used[d] = 1;
        cout << d << " " << rand()%maxd+1<< '\n';
    }
    return 0;
}

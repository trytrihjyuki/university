#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll MAXMASK_SQ = (1<<9) - 1;
const ll MAXMASK_L = (1<<5) - 1;
const ll MAXMASK_LSQ = (1<<10) - 1;

int n,p,MOD,ans=0;
int dp[(1<<10)+2][2];
bool badMasks[MAXMASK_SQ+2];
int cnt=0;
void printImage( int m1, int m2, int m3) {
    for (int i = 0; i < 5; i++)
    {
        if (m1&(1<<i)) cout<<"x";
        else cout<<".";
        if (m2&(1<<i)) cout<<"x";
        else cout<<".";
        if (m3&(1<<i)) cout<<"x\n";
        else cout<<".\n";
    }
    cout<<"\n";
}

bool check(int m1OG, int m2OG, int m3OG) {
    for (int i=0; i<3; i++){
        int m1 = (m1OG>>i);
        int m2 = (m2OG>>i);
        int m3 = (m3OG>>i);

        m1 = m1 & ((1<<3)-1);
        m2 = m2 & ((1<<3)-1);
        m3 = m3 & ((1<<3)-1);

        m2 = (m2<<3);
        m3 = (m3<<6);
        // if (badMasks[m1+m2+m3]) printImage(m1OG,m2OG,m3OG);
        if (badMasks[m1+m2+m3]) return false;
    }
    // printImage(m1OG,m2OG,m3OG);
    cnt++;
    return true;
}

int main() {
    scanf("%d %d %d",&n, &p, &MOD);
    for (int i=0; i<p; i++) {
        char s[3];
        int m = 0;
        for (int j=0; j<3; j++) {
            scanf("%s", s);
            for (int k=0; k<3; k++) {
                if (s[k]=='x') m += 1<<(j+k*3);
            }
        }
        badMasks[m] = true;
    }
    for (int m=0; m<=MAXMASK_LSQ; m++) {
        dp[m][0] = 0;
        dp[m][1] = 1;
    }
    for (int i=2; i<n; i++) {
        for (int m3=0; m3<=MAXMASK_L; m3++) {
            for (int m2=0; m2<=MAXMASK_L; m2++) {
                int m2m3 = m2+(m3<<5);
                dp[m2m3][i%2] = 0;
                for (int m1=0; m1<=MAXMASK_L; m1++) {
                    int m1m2 = m1+(m2<<5);
                    if (check(m1,m2,m3)) dp[m2m3][i%2] = (dp[m2m3][i%2] + dp[m1m2][(i-1)%2])%MOD;
                }
            }
        }
    }
    for (int m=0; m<=MAXMASK_LSQ; m++) ans = (ans + dp[m][(n-1)%2])%MOD;
    printf("%d",ans);
    return 0;
}
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
const ll MAXDIFF =  100000;
const ll MAXN = 2000;
const ll INF = int(1e6) + 10;

vector <int> klocki;

int main() {

    int n,allSum=0, e;
    scanf("%d",&n);

    for (int i=0; i<n; i++)
    {
        scanf("%d", &e);
        klocki.pb(e);
        allSum+=e;
    }

    int dp[2][int(allSum) + 5];
    // sort(klocki.begin(), klocki.end());

    for (int i=0; i<2; i++)
        for (int j=0; j<=int(allSum)+4; j++)
            dp[i][j] = -1;

    dp[0][0] = 0;
    int ans = INF;
    int curr, last;

    for (int i=1; i<=n; i++)
    {
        curr = i%2;
        last = !curr;
        for (int j = 0; j <= int(allSum/2); j++)
        {
            // cout << dp[i][j]<<endl;
            if (dp[last][j] != -1)
                dp[curr][j] = dp[last][j]; // nie bierzemy

            // cout << dp[i][j]<<endl;
            // cout<<"1ans: "<<ans<<endl;
            if (j >= klocki[i-1] && dp[last][j-klocki[i-1]] != -1)
            {
                dp[curr][j] = max(dp[curr][j], dp[last][j-klocki[i-1]] + klocki[i-1]); // dorzucamy do wiekszego
                if (dp[last][j-klocki[i-1]] > 0)
                    ans = min(ans,j);
                // cout <<"1. "<< dp[i][j]<<endl;
            // cout<<"2ans: "<<ans<<endl;
            }
            else
            {
                if (j <= klocki[i-1] && dp[last][klocki[i-1] - j] != -1)
                {
                    dp[curr][j] = max(dp[curr][j], dp[last][klocki[i-1] - j] + j); // dorzucamy do mniejszego i staje sie wiekszym
                    if (dp[last][klocki[i-1] - j] > 0)
                    {
                        // cout<<"DPPDPDP"<<dp[last][klocki[i-1] - j]<<"   "<<i<<" "<<j<<endl;
                        ans = min(ans,j);
                    }
                }
                // cout <<"2. "<< dp[i][j]<<endl;
            // cout<<"3ans: "<<ans<<" "<<i<<" "<<j<<endl;
            }

            if (j+klocki[i-1] <= int(allSum/2) && dp[last][j+klocki[i-1]] != -1)
            {
                dp[curr][j] = max(dp[curr][j], dp[last][j+klocki[i-1]]); // dorzucamy do mniejszego
                if (dp[last][j+klocki[i-1]] > 0)
                    ans = min(ans,j);
            }
            // cout << dp[i][j]<<"\nKONIEC\n"<<endl;
            // cout<<"4ans: "<<ans<<"\nDP[]:";
        // for (int kk = 0; kk <= int(allSum/2); kk++)
            // cerr << dp[j][kk] << " ";
        // cerr << "\n";
        }
    }


    if (dp[n%2][0] > 0)
    {
        printf("TAK\n%d",dp[n%2][0]);
        return 0;
    }
    printf("NIE\n%d",ans);
    return 0;
}
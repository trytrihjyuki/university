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
int n,t,c;
int main(){
    int response;
    cin>>n;
    int n_og = n;
    n = (n/3) * 3;
    int arr[n_og];
    for (int i = 0; i < n; i+=3)
    {
        int temp_ab,temp_ac,temp_bc;
        printf("? %d %d\n",i+1,i+1+1);
        fflush(stdout);
        cin>>temp_ab;
        printf("? %d %d\n",i+1,i+2+1);
        fflush(stdout);
        cin>>temp_ac;
        printf("? %d %d\n",i+1+1,i+2+1);
        fflush(stdout);
        cin>>temp_bc;

        arr[i] = (temp_ab + temp_ac - temp_bc) / 2;
        arr[i+1] = temp_ab - arr[i];
        arr[i+2] = temp_ac - arr[i];
    }

    for(int i = 0; i < n_og%3; i++)
    {
        printf("? %d %d\n",0+1,n+i+1);
        fflush(stdout);
        cin>>response;
        arr[n+i] = response - arr[0];
    }

    printf("!");
    for (int i = 0; i < n_og; i++)
    {
        printf(" %d",arr[i]);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#define ll long long
#define ull unsigned long long
#define zeroo 1000*50
#define infi 1000*5000
#define N 1005

int min(int a, int b){
    return (a > b) ? a : b;
}

int n,tab[1005];
bool dp[zeroo*2+10][N][55]; //dp[i][j][k] czy moge zbudowac sume i korzystajac jedynie z j pierwszych elementow oraz uzywajac k elementu
void odzyskaj(int suma, int itek, int uzyte){
    if(uzyte==0) return;
    printf("%d ",tab[itek]);
    for(int i=1; i<=n; i++){
        if(i!=itek && dp[suma-tab[itek]][i][uzyte-1]){
            odzyskaj(suma-tab[itek],i,uzyte-1);
            break;
        }
    }
}
int main(void){
    scanf("%d",&n);

    for(int i=1; i<=n; i++) scanf("%d",&tab[i]);

    for(int zasieg=0; zasieg<n; zasieg++){
        for(int suma=0; suma<=2*zeroo; suma++){
            for(int uzyte=0; uzyte<=50; uzyte++)
                dp[suma][zasieg][uzyte]=0;
        }
    }

    for(int zasieg=0; zasieg<n; zasieg++) dp[zeroo][zasieg][0] = 1;

    for(int i=1; i<=n; i++){
        for(int suma=0; suma<2*zeroo; suma++){
            for(int uzyte=0; uzyte<50; uzyte++){
                if(dp[suma][i-1][uzyte]){
                    dp[suma+tab[i]][i][uzyte+1] = 1;
                    dp[suma][i][uzyte] = 1;
                }
            }
        }
    }

    for(int uzyte=50; uzyte>=0; uzyte--){
        for(int i=n; i>=0; i--){
            if(dp[zeroo][i][uzyte]){
                odzyskaj(zeroo,i,uzyte);
                return 0;
            }
        }
    }


    return 0;
}
/*
5
1 2 5 -3 -2 

5
8 4 2 2 -8

5
1000000000000 -999999999999 4 -3 2

40
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
999 1000 1000 1000 1000 
1000 1000 1000 -465 -225

*/
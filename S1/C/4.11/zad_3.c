#include <stdio.h>
#include <stdbool.h>

#define infi 1e9
char siemano;
int tab[1100][1100],lewo[1100],prawo[1100];
int n,m,dp[1100][1100];
int ans = -1;
int max(int a, int b){
    return (a>b) ? a : b;
}
int main(void){
    scanf("%s",&siemano);
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d",&tab[i][j]);
            dp[i][j] = 1;
        }
    }
    for(int j=0; j<n; j++){
        tab[0][j] = tab[1][j];
        tab[j][0] = tab[j][1];
        tab[j][n+1] = tab[j][n];
    }

    for(int i=1; i<=n; i++){
        for(int j=0; j<=n+1; j++){
            prawo[j] = 1;
            lewo[j] = 1;
        }
        for(int j=1; j<=n; j++){
            if(tab[i-1][j]!=tab[i][j]) prawo[j] = max(prawo[j], dp[i-1][j] + 1);
            if(tab[i][j-1]!=tab[i][j]) prawo[j] = max(prawo[j-1] + 1,prawo[j]);
            //if(prawo[j] > 0) printf("prawo[%d]: %d\n",j,prawo[j]);
        }
        for(int j=n; j>=1; j--){
            if(tab[i-1][j]!=tab[i][j]) lewo[j] = max(lewo[j], dp[i-1][j] + 1);
            if(tab[i][j+1]!=tab[i][j]) lewo[j] = max(lewo[j+1] + 1,lewo[j]);
            //if(lewo[j] > 0) printf("lewo[%d]: %d\n",j,lewo[j]);
        }
        for(int j=1; j<=n; j++){
            //if(dp[i][j] > 0) printf("dp[%d][%d]: %d\n",i,j,dp[i][j]);
            dp[i][j] = max(prawo[j],lewo[j]);
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d",ans);

    return 0;
}
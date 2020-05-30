#include <stdio.h>
#include <stdbool.h>
#define ll long long
#define ull unsigned long long

ll tab[50],ans = 0;
int n,ans_q = 0;

void check_subset(int suma, int ilosc, int itek, ll mask){
    if(ilosc>10) return;
    if(!suma && ans_q < ilosc){
        ans = mask;
        ans_q = ilosc;
    }
    if(itek>=n) return;
    check_subset(suma+tab[itek],ilosc+1,itek+1, mask+(1ULL<<itek));
    check_subset(suma,ilosc,itek+1, mask);
}
int main(void){
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%lld",&tab[i]);
    check_subset(0,0,0,0);
    printf("%d\n",ans_q);
    for(int i=0; i<n; i++){
        if((1ULL<<i)&ans) printf("%lld ", tab[i]);
    }
    return 0;
}
/*

40
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
999999999999 8888888888 8888888888 8888888888 8888888888 
8888888888 8888888888 8888888888 -465 -225

*/
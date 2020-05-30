#include <stdio.h>
#include <stdbool.h>
#define ll long long
#define ull unsigned long long
#define N  21
int tab[N],ans[N],mapka[] = {'+','-','*','/'};
int n;
bool ans_dziewiczy = 0;

bool funkcja_rekurencyjna(int wynik, int itek, int dzialanie){
    if(itek==n){
        if(!ans_dziewiczy && wynik == 1){
            ans_dziewiczy = 1;
            return 1;
        }
        return 0;
    }
    bool wyn[4] = {0,0,0,0};
    if(dzialanie!=0) wyn[0] = funkcja_rekurencyjna(wynik+tab[itek],itek+1,0);
    if(wyn[0]){
        ans[itek] = 0;
        return 1;
    }
    if(dzialanie!=1) wyn[1] = funkcja_rekurencyjna(wynik-tab[itek],itek+1,1);
    if(wyn[1]){
        ans[itek] = 1;
        return 1;
    }
    if(dzialanie!=2) wyn[2] = funkcja_rekurencyjna(wynik*tab[itek],itek+1,2);
    if(wyn[2]){
        ans[itek] = 2;
        return 1;
    }
    if(dzialanie!=3 && tab[itek]!= 0) wyn[3] = funkcja_rekurencyjna(wynik/tab[itek],itek+1,3);
    if(wyn[3]){
        ans[itek] = 3;
        return 1;
    }
    return 0;
}
int main(void){
    scanf("%d",&n);

    for(int i=0; i<n; i++) scanf("%d",&tab[i]);
    bool flag = 0;
    for(int i=0; i<4; i++) flag = flag || funkcja_rekurencyjna(tab[0], 1, i);
    if(!flag){
        printf("nie da się");
        return 0;
    }
    printf("\n\n%d ",tab[0]);
    for(int i=1; i<n; i++) printf("%c %d ", mapka[ans[i]], tab[i]);
    
    return 0;
}

/*
3
2 2 1

5
10 8 0 2 1

*/
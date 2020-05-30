#include <stdio.h>
#include <stdbool.h>
#define ll long long
const bool debug = 0;
#define deb if(debug)
#define N 20
#define M 20
int n,m;
bool wypisalem = 0;
ll licznik = 1;
int tab[N][N],wiersze_wolne[N],kolumny_wolne[N],sumy_wierszy[N],sumy_kolumn[N];
void solve(){
    deb{
        printf("siemanderko, nowe wywolanie\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                printf("%d ",tab[i][j]);
            }
            printf("\n");
        }
    }
    if(wypisalem) return;
    bool flag = 0;
    for(int i=0; i<n; i++){
        if(sumy_wierszy[i]&&!wiersze_wolne[i]) return;
        if(wiersze_wolne[i]) flag = 1;
    }
    for(int j=0; j<m; j++){
        if(sumy_kolumn[j]&&!kolumny_wolne[j]) return;
        if(kolumny_wolne[j]) flag = 1;
    }
    if(!flag&&!wypisalem){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++) printf("%d ",tab[i][j]);
            printf("\n");
        }
        wypisalem = 1;
        return;
    }
    deb printf("nie\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(!tab[i][j]){
                if(wiersze_wolne[i]==1){ //oczywiste bo ostatni w wierszu
                    if(sumy_wierszy[i]>=-9&&sumy_wierszy[i]<=9&&sumy_wierszy[i]){
                        tab[i][j] = -sumy_wierszy[i];
                        kolumny_wolne[j]--;
                        wiersze_wolne[i]--;
                        sumy_kolumn[j]-=sumy_wierszy[i];
                        sumy_wierszy[i] = 0;
                        solve();
                        kolumny_wolne[j]++;
                        wiersze_wolne[i]++;
                        sumy_wierszy[i]-=tab[i][j];
                        sumy_kolumn[j]-=tab[i][j];
                        tab[i][j] = 0;
                    }
                    return;
                }
                else{
                    if(kolumny_wolne[j]==1){ //ocztywiste bo ostatni w kolumnie
                        deb printf("siemanko %d\n",j);
                        if(sumy_kolumn[j]>=-9&&sumy_kolumn[j]<=9&&sumy_kolumn[j]){
                            kolumny_wolne[j]--;
                            wiersze_wolne[i]--;
                            tab[i][j] = -sumy_kolumn[j];
                            sumy_wierszy[i]-=sumy_kolumn[j];
                            sumy_kolumn[j] = 0;
                            solve();
                            kolumny_wolne[j]++;
                            wiersze_wolne[i]++;
                            sumy_wierszy[i]-=tab[i][j];
                            sumy_kolumn[j]-=tab[i][j];
                            tab[i][j] = 0;
                        }
                        return;
                    }
                    else{
                        for(int liczba=1; liczba<=9; liczba++){
                            if(liczba){
                                tab[i][j] = liczba;
                                wiersze_wolne[i]--;
                                kolumny_wolne[j]--;
                                sumy_wierszy[i]+=liczba;
                                sumy_kolumn[j]+=liczba;
                                solve();
                                tab[i][j] = 0;
                                wiersze_wolne[i]++;
                                kolumny_wolne[j]++;
                                sumy_wierszy[i]-=liczba;
                                sumy_kolumn[j]-=liczba;
                                //////////////
                                liczba*=-1;
                                tab[i][j] = liczba;
                                wiersze_wolne[i]--;
                                kolumny_wolne[j]--;
                                sumy_wierszy[i]+=liczba;
                                sumy_kolumn[j]+=liczba;
                                solve();
                                tab[i][j] = 0;
                                wiersze_wolne[i]++;
                                kolumny_wolne[j]++;
                                sumy_wierszy[i]-=liczba;
                                sumy_kolumn[j]-=liczba;
                                liczba*=-1;
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
}
int main(void){
    scanf("%d%d",&m,&n);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) scanf("%d",&tab[i][j]);
    }
    for(int i=0; i<N; i++){
        sumy_kolumn[i] = 0;
        sumy_wierszy[i] = 0;
        kolumny_wolne[i] = 0;
        wiersze_wolne[i] = 0;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(!tab[i][j]){
                wiersze_wolne[i]++;
                kolumny_wolne[j]++;
            }
            sumy_kolumn[j]+=tab[i][j];
            sumy_wierszy[i]+=tab[i][j];
        }
    }
    solve();
    if(!wypisalem) printf("Nie można znaleźć odpowiedzi");
    return 0;
}
/*

4 4
0 1 1 1
0 0 1 1
0 0 0 1
0 0 0 0

3 3
0 1 2
4 0 -1
0 0 0

5 4
0 0 0 0 1
1 1 1 1 0
2 2 2 2 0
3 3 3 3 0

10 10
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0

5 6
0 0 0 0 0
0 0 0 0 0
1 1 1 1 0
1 1 1 1 0
1 1 1 1 0
1 1 1 1 0

*/
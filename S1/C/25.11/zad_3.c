#include <stdio.h>
#include <stdbool.h>
#define N 200
int n,m,licznik_s,licznik_l;
struct punkt{
    int i;
    int j;
};
int plansza[N][N];
char plansza_og[N][N];
struct punkt legowiska[N*N];
struct punkt sladj[N];
bool koncze_w_slad[N]; //1  jezeli moge skonczjc sciezke hamiltonowska w tjm sladzie 0 jak nie moge
bool visited[N][N];
bool graf_sladow[N][N];
bool polaczony_legowiskiem[N];
bool visited_slady[N];
void zeruj_visited(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) visited[i][j] = 0;
    }
}
void gen_polaczenia(struct punkt vb,int indeks_ojca_slada){
    visited[vb.i][vb.j] = 1;
    struct punkt sasiedzi[] = {{vb.i-1,vb.j},{vb.i+1,vb.j},{vb.i,vb.j-1},{vb.i,vb.j+1}};
    for(int sasiad=0; sasiad<4; sasiad++){
        struct punkt v = sasiedzi[sasiad];
        switch(plansza[v.i][v.j]){
            case 1:
                break;
            case 2:
                if(!visited[v.i][v.j])
                    gen_polaczenia(v,indeks_ojca_slada);
                break;
            case 3:
                for(int i = 0; i<licznik_s; i++){
                    if(!visited[v.i][v.j] && v.i == sladj[i].i && v.j == sladj[i].j){
                        graf_sladow[indeks_ojca_slada][i] = 1;
                        graf_sladow[i][indeks_ojca_slada] = 1;
                    }
                }
                break;
            case 4:
                if(!visited[v.i][v.j]){
                    polaczony_legowiskiem[indeks_ojca_slada] = 1;
                    gen_polaczenia(v,indeks_ojca_slada);
                }
                break;
        }
    }
}
void gen_sciezki(int used, int vb){
    if(used==0){
        for(int i=0; i<licznik_s; i++){
            if(polaczony_legowiskiem[i]){
                visited_slady[i] = 1;
                gen_sciezki(1,i);
                visited_slady[i] = 0;
            }
        }
        return;
    }
    if(used==licznik_s){
        koncze_w_slad[vb] = 1;
        return;
    }
    for(int i=0; i<licznik_s; i++){
        if(!visited_slady[i] && graf_sladow[vb][i]){
            visited_slady[i] = 1;
            gen_sciezki(used+1,i);
            visited_slady[i] = 0;
        }
    }
}
void koloruj(struct punkt vb){
    plansza_og[vb.i][vb.j] = 'X';
    visited[vb.i][vb.j] = 1;
    struct punkt sasiedzi[] = {{vb.i-1,vb.j},{vb.i+1,vb.j},{vb.i,vb.j-1},{vb.i,vb.j+1}};
    for(int sasiad=0; sasiad<4; sasiad++){
        struct punkt v = sasiedzi[sasiad];
        switch(plansza[v.i][v.j]){
            case 1:
                break;
            case 2:
                if(!visited[v.i][v.j])
                    koloruj(v);
                break;
            case 3:
                break;
            case 4:
                if(!visited[v.i][v.j])
                    koloruj(v);
                break;
        }
    }
}
int main(void){
    scanf("%d%d",&m,&n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            char pole;
            do{
                pole = getchar();
            }while(pole== ' '|| pole == '\n');
            plansza_og[i][j] = pole;
            switch(pole) {
                case '#' :
                    plansza[i][j] = 1;
                    break;
                case '.' :
                    plansza[i][j] = 2;
                    break;
                case 'S':
                    plansza[i][j] = 3;
                    struct punkt slad_b = {i,j};
                    sladj[licznik_s++] = slad_b;
                    break;
                case 'L':
                    plansza[i][j] = 4;
                    struct punkt legowisko_b = {i,j};
                    legowiska[licznik_l++] = legowisko_b;
                    break;
            }
        }
    }
    //tworzenie ramek z haszj
    for(int i=0; i<=n; i++){
        plansza[i][0] = 1;
        plansza[i][m+1] = 1;
    }
    for(int j=0; j<=m; j++){
        plansza[0][j] = 1;
        plansza[n+1][j] = 1;
    }
    //tworze tablice jako graf miedzj sladami
    for(int i=0; i<licznik_s; i++){
        zeruj_visited();
        gen_polaczenia(sladj[i],i);
    }
    //tworze tablice czy slad jest polaczony z legoiwskiem
    gen_sciezki(0,0);
    //koloruj wynik
    bool flag = 0;
    for(int i=0; i<licznik_s; i++){
        if(koncze_w_slad[i]){
            zeruj_visited();
            koloruj(sladj[i]);
            flag = 1;
        }
    }
    if(!flag){
       for(int i=0; i<licznik_l; i++){
            zeruj_visited();
            koloruj(legowiska[i]);
       }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(plansza_og[i][j]=='S'||plansza_og[i][j]=='L') plansza_og[i][j] = '.'; 
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) printf("%c",plansza_og[i][j]);
        printf("\n");
    }
    return 0;
}

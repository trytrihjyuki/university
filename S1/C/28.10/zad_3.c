#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int tab[1040][1040];
void solve(int n, int m){
    int rr = 1, rs = 1, rd = 1;
    //rr
    int poprzedni = tab[0][0];
    if(poprzedni==1) rr++;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(tab[i][j]!=poprzedni) rr++;
            poprzedni = tab[i][j];
        }
    }
    //rs
    poprzedni = tab[0][0];
    if(poprzedni==1) rs++;
    for(int i=0; i<n; i++){
        if(i%2){
            for(int j=m-1; j>=0; j--){
                if(tab[i][j]!=poprzedni) rs++;
                poprzedni = tab[i][j];
            }
        }
        else{
            for(int j=0; j<m; j++){
                if(tab[i][j]!=poprzedni) rs++;
                poprzedni = tab[i][j];
            }
        }
    }
    //rd
    poprzedni=0;
    int x = 0, y = 0;
    int licznik = 0;
    printf("tab[%d][%d]: %d \n tab[%d][%d]: %d \n",0,0,tab[0][0],1,0,tab[1][0]);
    while(x!=n-1||y!=m-1){
        if(licznik%2){ //z gory do dolu
            while(x>0&&y<m-1){
                if(poprzedni!=tab[y][x]) printf("[1] zmieniam w %d %d \n",x,y);
                if(poprzedni!=tab[y][x]) rd++;
                poprzedni = tab[y][x];
                x--;
                y++;
            }
            if(poprzedni!=tab[y][x]) printf("[2] zmieniam w %d %d \n",x,y);
            if(poprzedni!=tab[y][x]) rd++;
            poprzedni = tab[y][x];
            if(x==0&&y!=m-1) y++;
            else x++;
        }
        else{ //z dolu do goru
            while(x<n-1&&y>0){
                if(poprzedni!=tab[y][x]) printf("[3] zmieniam w %d %d \n",x,y);
                if(poprzedni!=tab[y][x]) rd++;
                poprzedni = tab[y][x];
                x++;
                y--;
            }
            if(poprzedni!=tab[y][x]) printf("[4] zmieniam w %d %d \n",x,y);
            if(poprzedni!=tab[y][x]) rd++;
            poprzedni = tab[y][x];
            if(x==n-1) y++;
            else x++;
        }
        licznik++;
    }
    if(poprzedni!=tab[y][x]) printf("[5] zmieniam w %d %d \n",x,y);
    if(poprzedni!=tab[y][x]) rd++;
    poprzedni = tab[y][x];
    printf("%d %d %d",rr,rs,rd);
}
int main(void){
    char s[10];
    int n,m;
    for(int i=0; i<1030; i++){
        for(int j=0; j<1030; j++){
            tab[i][j] = 0;
        }
    }
    scanf("%s",s);
    if(s[0]=='P'&&s[1]=='1'){
        scanf("%d %d", &n, &m);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                scanf("%d",&tab[i][j]);
            }
        }
        solve(n,m);
    }
    else{
        scanf("%d",&n);
        int dlugosc,zero_jeden = 0, wejscie[1048500],itek = 0,a;
        while(scanf("%d",&a) != EOF)
            wejscie[itek++]=a;
        if(s[1]=='R'){
            int itek = 1;
            dlugosc = wejscie[0];
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    if(dlugosc>0){
                        tab[i][j] = zero_jeden;
                        dlugosc--;
                    }
                    else{
                        zero_jeden = (zero_jeden + 1)%2;
                        tab[i][j] = zero_jeden;
                        dlugosc = wejscie[itek++] - 1;
                    }
                }
            }
            solve(n,n);
        }
        if(s[1]=='S'){
            int itek = 1;
            dlugosc = wejscie[0];
            for(int i=0; i<n; i++){
                if(i%2){
                    for(int j=n-1; j>=0; j--){
                        if(dlugosc>0){
                            tab[i][j] = zero_jeden;
                            dlugosc--;
                        }
                        else{
                            zero_jeden = (zero_jeden + 1)%2;
                            tab[i][j] = zero_jeden;
                            dlugosc = wejscie[itek++] - 1;
                        }
                    }
                }
                else{
                    for(int j=0; j<n; j++){
                        if(dlugosc>0){
                            tab[i][j] = zero_jeden;
                            dlugosc--;
                        }
                        else{
                            zero_jeden = (zero_jeden + 1)%2;
                            tab[i][j] = zero_jeden;
                            dlugosc = wejscie[itek++] - 1;
                        }
                    }
                }
            }
            solve(n,n);
        }
        if(s[1]=='D'){
            int itek = 1;
            dlugosc = wejscie[0];
            int x = 0, y = 0;
            int licznik = 0;
            while(x!=n-1||y!=n-1){
                if(licznik%2){ //z gory do dolu
                    while(x>0&&y<n-1){
                        if(dlugosc>0){
                            tab[y][x] = zero_jeden;
                            dlugosc--;
                        }
                        else{
                            zero_jeden = (zero_jeden + 1)%2;
                            tab[y][x] = zero_jeden;
                            dlugosc = wejscie[itek++] - 1;
                        }
                        x--;
                        y++;
                    }
                    if(dlugosc>0){
                        tab[y][x] = zero_jeden;
                        dlugosc--;
                    }
                    else{
                        zero_jeden = (zero_jeden + 1)%2;
                        tab[y][x] = zero_jeden;
                        dlugosc = wejscie[itek++] - 1;
                    }
                    if(x==0&&y!=n-1) y++;
                    else x++;
                }
                else{ //z dolu do goru
                    while(x<n-1&&y>0){
                        if(dlugosc>0){
                            tab[y][x] = zero_jeden;
                            dlugosc--;
                        }
                        else{
                            zero_jeden = (zero_jeden + 1)%2;
                            tab[y][x] = zero_jeden;
                            dlugosc = wejscie[itek++] - 1;
                        }
                        x++;
                        y--;
                    }
                    if(dlugosc>0){
                        tab[y][x] = zero_jeden;
                        dlugosc--;
                    }
                    else{
                        zero_jeden = (zero_jeden + 1)%2;
                        tab[y][x] = zero_jeden;
                        dlugosc = wejscie[itek++] - 1;
                    }
                    if(x==n-1) y++;
                    else x++;
                }
                licznik++;
            }
            if(dlugosc>0){
                tab[y][x] = zero_jeden;
                dlugosc--;
            }
            else{
                zero_jeden = (zero_jeden + 1)%2;
                tab[y][x] = zero_jeden;
                dlugosc = wejscie[itek++] - 1;
            }
        solve(n,n);
        }
    }
    printf("Tablica w formacie P1:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d", tab[i][j]);
        }
        printf("\n");
    }
    return 0;
}
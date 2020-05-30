#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int map_to_ascii[500], map_to_ind[500],permutacja[500],klucz_ind[500],tekst_ind[500],ans[500];
bool flag = 0;
char klucz[600], tekst[600];
void make_map(){
    for(int i=0; i<500; i++) map_to_ind[i] = -1;
    char start = '0';
    for(int i=0; i<=9; i++) map_to_ascii[i] = start + i;
    start = 'A';
    for(int i=0; i<=25; i++) map_to_ascii[i+10] = start + i;
    start = 'a';
    for(int i=0; i<=25; i++) map_to_ascii[i+36] = start + i;
    map_to_ascii[62] = ' ';
    map_to_ascii[63] = ',';

    for(int i=0; i<=256; i++){
        for(int j=0; j<=63; j++){
            if(map_to_ascii[j]==i)
                map_to_ind[i]=j;
        }
    }
}
int main(void){
    make_map();
    char operation[1000];
    scanf("%s", operation);
    for(int i=0; i<64; i++) scanf("%d", &permutacja[i]);
    scanf("\n");
    scanf("%[^\n]%*c", klucz);
    scanf("%[^\n]%*c", tekst);
    for(unsigned int i=0; i<strlen(klucz); i++){
        int siema = klucz[i];
        if(map_to_ind[siema]==-1){
            printf("UNSUPPORTED_ALPHABET\n");
            return 0;
        }
        klucz_ind[i] = map_to_ind[siema];
    }
    for(unsigned int i=0; i<strlen(tekst); i++){
        int siema = tekst[i];
        if(map_to_ind[siema]==-1){
            printf("UNSUPPORTED_ALPHABET\n");
            return 0;
        }
        tekst_ind[i] = map_to_ind[siema];
    }
    for(unsigned int i=0; i<strlen(klucz); i++)
        klucz_ind[i] = permutacja[klucz_ind[i]]; 
    
    //for(unsigned int i=0; i<strlen(klucz); i++){
    //    printf("Zwykły klucz[%d]: %d\n", i, klucz_ind[i]);
    //}
    if(operation[0]!='e'){
        for(unsigned int i=0; i<strlen(klucz); i++){
            klucz_ind[i] = (64-klucz_ind[i])%64;
          //  printf("Odwrócony klucz[%d]: %d\n", i, klucz_ind[i]);
        }
    }
    for(unsigned int i=0; i<strlen(tekst); i++){
        int dlugosc_klucza = strlen(klucz);
        ans[i]=(tekst_ind[i]+klucz_ind[i%(dlugosc_klucza)])%64;
    }
    for(unsigned int i=0; i<strlen(tekst); i++){
        printf("%c", map_to_ascii[ans[i]]);
    }
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int dlugosc_paska = 10;
int main(void){
    char c;
    int zliczanko[256],wszystkie;
    for(int i=0; i<256; i++) zliczanko[i] = 0;
    while((c = getchar()) != '\n'){
        if(isgraph(c)){
            int c_int = c;
            zliczanko[c_int]++;
            wszystkie++;
        }
    }
    for(int i=0; i<256; i++){
        if(zliczanko[i]){
            double czesc = (double)zliczanko[i]/wszystkie;
            printf("%c [", i);
            for(int j=0; j<round(czesc*dlugosc_paska); j++) printf("*");
            for(int j=round(czesc*dlugosc_paska); j<dlugosc_paska; j++) printf(" ");
            printf("]\n");
        }
    }
    return 0;
}
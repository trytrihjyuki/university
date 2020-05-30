#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main(void){
    char c;
    bool kropka = 0, krop_przec = 0;
    while((c = getchar()) != EOF){
        bool flag = 1;
        if(isalpha(c) && kropka){
            printf("%c",toupper(c));
            flag = 0;
            kropka = 0;
            krop_przec = 0;
        }
        if(isalpha(c) && flag){
            printf("%c",c);
            flag = 0;
            krop_przec = 0;
            kropka = 0;
        }
        if(c == '.' && flag){
            kropka = 1;
            krop_przec = 1;
            printf(". ");
            flag = 0;
        }
        if(c == ',' && flag){
            krop_przec = 1;
            printf(", ");
            flag = 0;
        }
        if((!krop_przec || c != ' ') && flag){
            printf("%c",c);
            flag = 0;
            krop_przec = 0;
        }
    }
    printf("\n");
    return 0;
}
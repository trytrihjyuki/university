#include <stdio.h>
#include <string.h>
#include <stdbool.h>
const bool debug = 0;
#define deb if(debug)

char test[100100];
int stos[101000];
int licznik = 0;
void new_f(){
    stos[licznik++] = 0;
}
void add_to_f(){
    stos[licznik]++;
}
void remove_f(){
    stos[licznik] = 0;
    licznik--;
}
int pomin_spacje(unsigned int itek){
    while(itek<strlen(test)&&test[itek]==' ') itek++;
    return itek;
}
int main(void){
    unsigned int itek = 0;
    scanf("%[^\n]",test);
    while(itek<strlen(test)){
        deb printf("\nJestem w %d\n",itek);
        itek = pomin_spacje(itek);
        if(itek>=strlen(test)) return 0;
        if(test[itek]=='('){
            if(stos[licznik]) printf(", ");
            deb printf("Zaczynam funkcje kolejna\n");
            //musze wczytać funkcję teraz
            itek++;
            itek = pomin_spacje(itek);
            while(itek<strlen(test)&&test[itek]!=' '&&test[itek]!=')') printf("%c",test[itek++]);
            printf("(");
            new_f();
        }
        else{ //argumenty wczytyuję
            if(test[itek]==')'){
                printf(")");
                remove_f();
                add_to_f();
                itek++;
            }
            else{
                if(stos[licznik]) printf(", ");
                else add_to_f();
                deb printf("Wczytuję argumenty funkcji\n");
                while(itek<strlen(test)&&test[itek]!=' '&&test[itek]!=')'){
                    printf("%c",test[itek]);
                    itek++;
                }
                itek = pomin_spacje(itek);
                if(test[itek]==')'){
                    printf(")");
                    remove_f();
                    add_to_f();
                    itek++;
                }
            }
        }
    }
    return 0;
}
/*

   (  f      x           y  )  

*/
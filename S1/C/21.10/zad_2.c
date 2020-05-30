#include <stdio.h>
#include <string.h>
/*
1 (
2 {
3 [
4 )
5 }
6 ]
*/
int staczek[10005];
int top = -1;
int indeks_naw(char c){
    if(c=='(') return 1;
    if(c=='{') return 2;
    if(c=='[') return 3;
    if(c==')') return 4;
    if(c=='}') return 5;
    if(c==']') return 6;
    return 7;
}
void add(int elem){
    top+=1;
    staczek[top] = elem;
}
void del(void){
    staczek[top] = 0;
    top-=1;
}
int top_elem(){
    return staczek[top];
}
int main(void){
    char string[10005];
    scanf("%[^\n]%*c", string);
    for(unsigned int i=0; i<strlen(string); i++){
        int indeks = indeks_naw(string[i]);
        if(indeks <= 3) add(indeks);
        else{
            if(top_elem() != indeks-3){
                printf("Zły nawias zamyka.");
                return 0;
            }
            else
                del();
        }
    }
    if(top != -1) printf("Nie domknięte nawiasy");
    else printf("Dobrze");
    return 0;
}
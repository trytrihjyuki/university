#include <stdio.h>
#include <stdlib.h>

int main(void){
    unsigned long long sr, l=0, r=60000;
    while(l<r){
        sr = (l+r)/2;
        size_t blok = sr*(1<<20);
        void* ptr = malloc(blok);
        if(ptr==NULL) r = sr-1;
        else{
            l = sr+1;
            free(ptr);
        }
    }
    printf("Maksymalnie udało mi się zalokować %lld Mb\n",sr);
    return 0;
}
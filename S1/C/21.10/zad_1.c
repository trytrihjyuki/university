#include <stdio.h>

int main(void){
    int n,m,t,usuwane;
    scanf("%d%d%d",&n, &m, &t);
    usuwane =  t-1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(usuwane%(t) >= j%(t)) printf("%c", '*');
            else printf(" ");
        }
        usuwane = usuwane-1 == 0 ? t : usuwane-1;
        printf("\n");
    }
    return 0;
}
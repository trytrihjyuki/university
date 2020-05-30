#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(){
    double z;
    scanf("%lf", &z);
    double wyn = 1.0, wyn_poprzedni = 0.0;
    int n = 1.0;
    while(wyn > wyn_poprzedni){
        n+=1;
        wyn_poprzedni = wyn;
        wyn+=pow(1/n,z);
    }
    printf("%lf %d",wyn,n);
    return 0;
}
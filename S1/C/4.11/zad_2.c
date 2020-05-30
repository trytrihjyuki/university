#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
const int r = 60;
const float delta = 1.0;
const double pi = 2*3.14159265;
int main(void){
    int tab[2*r+100][2*r+100];
    int h,m;
    scanf("%d%d",&h,&m);
    if(h>12.01) h-=12;
    for(int i=-r; i<=r; i++){
        for(int j=-r; j<=r; j++){
            if(i*i + j*j < r*r) tab[i+r][j+r] = 1;
            else tab[i+r][j+r] = 0;
        }
    }
    double sinus_h = (double)sin((double)(h/12.0 - 0.25)*pi);
    double cosinus_h = (double)cos((double)(h/12.0 - 0.25)*pi);
    double sinus_m = (double)sin((double)(m/60.0 - 0.25)*pi);
    double cosinus_m = (double)cos((double)(m/60.0 - 0.25)*pi);
    for(int i=-r; i<=r; i++){
        for(int j=-r; j<=r; j++){
            if(tab[i+r][j+r]){
                double odl = sqrt(i*i + j*j);
                if(abs(odl*sinus_h-(double)i) + abs(odl*cosinus_h-(double)j) < delta)
                    tab[i+r][j+r]+=2;
                if(abs(odl*sinus_m-(double)i) + abs(odl*cosinus_m-(double)j) < delta)
                    tab[i+r][j+r]+=4;
            }
        }
    }
    for(int i=0; i<=2*r; i++){
        for(int j=0; j<=2*r; j++){
            switch (tab[i][j]){
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf(".");
                    break;
                case 3:
                    printf("+");
                    break;
                case 5:
                    printf("=");
                    break;
                case 7:
                    printf("#");
                    break;
            }
        }
        printf("\n");
    }
    return 0;
}
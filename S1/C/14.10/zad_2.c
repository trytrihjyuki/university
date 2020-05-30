#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX(x, y) (((x) < (y)) ? (x) : (y))
bool czy_pierwsza(int a){
    int dzielniki = 0;
    for(int i=1; i*i<=a; i++){
        if(!(a%i))
            dzielniki = (a/i == i) ? dzielniki + 1 : dzielniki + 2;
    }
    return dzielniki == 2;
}
int najmniejszy_rozny_czynnik(int m, int n){
    for(int i=2; ; i++){
        if(czy_pierwsza(i)){
            if(m%i != n%i) return i;
        }
    }
}
int main(){
    int m,n;
    double wyn=-10000;
    for(int m_i=3; m_i<=1000; m_i++){
        for(int n_i=m_i+1; n_i<=1000; n_i++){
            if(najmniejszy_rozny_czynnik(m_i, n_i)/log(n_i) > wyn){
                wyn = najmniejszy_rozny_czynnik(m_i, n_i)/log(n_i);
                n = n_i;
                m = m_i;
            } 
        }
    }

    printf("%d %d", m, n);
    return 0;
}
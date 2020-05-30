#include <stdio.h>
#include <stdbool.h>

int main(void){
    char c;
    bool poprzedni = 0;
    int b_c = 0, m_c = 0;
    while((c = getchar()) != EOF){
        for(int i=(1<<7); i>=1; i/=2){
            if((bool)(i&c)==poprzedni){
                if(m_c<b_c) m_c = b_c;
                b_c = (bool)(i&c);
            }
            else
                b_c++;
            poprzedni = (bool)(i&c);
        }
    }
    if(m_c<b_c) m_c = b_c;
    printf("%d",m_c);
    return 0;
}
#include <stdio.h>
#include <string.h>
#define PRINTBIN(napis) \
    do{\
        int itek = 0,suma = 0;\
        if(strlen(#napis)%8){\
            for(itek=0; itek<(int)strlen(#napis)%8; itek++){\
                if(#napis[itek]=='1') suma+=(1<<((int)strlen(#napis)%8-itek-1));\
            }\
            printf("%c",suma);\
        }\
        while(itek<(int)strlen(#napis)){\
            suma = 0;\
            for(int i=itek; i<itek+8; i++)\
                if(#napis[i]=='1') suma+=(1<<(7-(i-itek)));\
            itek+=8;\
            printf("%c",suma);\
        }\
    }while(0);\

int main(void){
    //char string[100];
    //scanf("%s",string);
    //do{
    //    int itek = 0;
    //    //printf("siemanderko %d\n", (int)strlen(string));
    //    int suma = 0;
    //    if(strlen(string)%8){
    //        //printf("nie dzieli");
    //        for(itek=0; itek<(int)strlen(string)%8; itek++){
    //            if(string[itek]=='1') suma+=(1<<((int)strlen(string)%8-itek-1));
    //        }
    //        printf("%c",suma);
    //    }
    //    while(itek<(int)strlen(string)){
    //        //printf("\n%d itek\n",itek);
    //        suma = 0;
    //        for(int i=itek; i<itek+8; i++)
    //            if(string[i]=='1') suma+=(1<<(7-(i-itek)));
    //        itek+=8;
    //        printf("%c",suma);
    //    }
    //}while(0);
for(int i = 0; i < 10; i++)
    if(i%2){
        PRINTBIN(111010001011010010100100001010);
    }
    else{
        PRINTBIN(1010);
    }
}
// 10100101
// 0011011000111001
// 111001
// 011000010110001001100011
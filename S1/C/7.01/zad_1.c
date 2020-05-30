#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *klucz = fopen(argv[0], "rb");
    FILE *szyfrowany = fopen(argv[1], "rb+");
    bool klucz_koniec = 1, szyfrowany_koniec = 1;
    char buffer_klucz[1];
    char buffer_szyfrowany[1];
    if(klucz&&szyfrowany){ //pliki otwarte oba
        while(klucz_koniec || szyfrowany_koniec){ // przynajmniej jedenk się nie skończył
            if(fread(buffer_klucz, sizeof(buffer_klucz), 1, klucz) == 1){
                //dobrze wczytal
            }
            else{ //skończył się plik
                fseek(klucz, 0, SEEK_SET);
                klucz_koniec = 0;
                if(klucz_koniec || szyfrowany_koniec)
                    fread(buffer_klucz, sizeof(buffer_klucz), 1, klucz);
            }
            if(fread(buffer_szyfrowany, sizeof(buffer_szyfrowany), 1, szyfrowany) == 1){
                //dobrze wczytal
            }
            else{ //skończył się plik
                fseek(szyfrowany, 0, SEEK_SET);
                szyfrowany_koniec = 0;
                if(klucz_koniec || szyfrowany_koniec)
                    fread(buffer_szyfrowany, sizeof(buffer_szyfrowany), 1, szyfrowany);
            }

            char buffer[] = {buffer_szyfrowany[0]^buffer_klucz[0]};
            if(klucz_koniec || szyfrowany_koniec){
                fseek(szyfrowany, -1L, SEEK_CUR);
                fwrite(buffer, sizeof(buffer), 1, szyfrowany);
            }

        }
    }

    fclose(klucz);
    fclose(szyfrowany);
    return 0;
}
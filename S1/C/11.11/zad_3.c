#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const bool debug = 1;
const bool debug1 = 1;
const bool debug2 = 1;

#define N 1000000
#define deb if(debug)
#define deb1 if(debug1)
#define deb2 if(debug2)

struct negacja
{
    int typ_uzaleznionego;
    int typ_uzalezniajacego;
    int indeks_uzaleznionego;
    int indeks_uzalezniajacego;
    bool wart_trigerujaca;
};

char s[10],sygnatura[N],punkt_wejscie[N];
int indeks,itek_2 = 0,Nx,Ny,x,y,negacje_itek=0;
unsigned int itek = 0;
int bit_indeksu[N],bity[N][2];
int bit_ind_to_number[N];
char y_s[N];
char x_s[N];
bool usedd[N];
struct negacja negacje[N];

int min(int a, int b){
    return (a > b) ? b : a;
}

int max(int a, int b){
    return (a < b) ? b : a;
}

void wypisz_input(void){
    printf("sygnatura:\n");
    for(unsigned int i=0; i<strlen(sygnatura); i++)
        printf("%c",sygnatura[i]);
    printf("\npunkt_wejscie:\n");
    for(unsigned int i=0; i<strlen(punkt_wejscie); i++)
        printf("%c",punkt_wejscie[i]);
    printf("\nindeks:\n%d",indeks);
    printf("\n");
}

void wypisz_bity(int x, int y){
    printf("bitowa reprezentacja liczby: %d\n",x);
    for(int i=0; i<=max(Nx,Ny); i++) printf("x%d = %d, ",i,bity[i][0]);
    printf("\n\nbitowa reprezentacja liczby: %d\n",y);
    for(int i=0; i<=max(Nx,Ny); i++) printf("y%d = %d, ",i,bity[i][1]);
    printf("\n");
}

void swtorz_x_y(int itek_4, int itek_5){
    int pot10 = 1;
    for(int i=itek_4-1; i>=0; i--){
        y+=(y_s[i]-48)*pot10;
        pot10*=10;
    }
    pot10 = 1;
    for(int i=itek_5-1; i>=0; i--){
        x+=(x_s[i]-48)*pot10;
        pot10*=10;
    }
}
void wykonaj_negacje(int n_b){
    // if(usedd[n_b]) return;
    // for(int i=0; i<negacje_itek; i++){
    //     if(i!=n_b){
    //         if(negacje[i].typ_uzaleznionego == negacje[n_b].typ_uzalezniajacego && negacje[i].indeks_uzaleznionego == negacje[n_b].indeks_uzalezniajacego)
    //         {
    //             wykonaj_negacje(i);
    //             //struct negacja neg = negacje[i];
    //             //if(bity[neg.indeks_uzalezniajacego][neg.typ_uzalezniajacego] == neg.wart_trigerujaca){
    //             //    deb printf("negacja[%d]: neguję %d bit typu %d\n",n_b+1, neg.indeks_uzaleznionego, neg.typ_uzaleznionego);
    //             //    bity[neg.indeks_uzaleznionego][neg.typ_uzaleznionego] = !bity[neg.indeks_uzaleznionego][neg.typ_uzaleznionego];
    //             //    usedd[i] = 1;
    //             //}            
    //         }
    //     }
    // }
    struct negacja neg = negacje[n_b];
    if(bity[neg.indeks_uzalezniajacego][neg.typ_uzalezniajacego] == neg.wart_trigerujaca){
        deb printf("negacja[%d]: neguję %d bit typu %d\n",n_b+1, neg.indeks_uzaleznionego, neg.typ_uzaleznionego);
        bity[neg.indeks_uzaleznionego][neg.typ_uzaleznionego] = !bity[neg.indeks_uzaleznionego][neg.typ_uzaleznionego];
    }
}
int main(void){
    scanf("%s", s);
    scanf("\n");
    scanf("%[^\n]%*c", sygnatura);
    scanf("\n");
    //Mapa tlumaczaca chary na inty
    for(int i=(int)'0'; i<=(int)'9'; i++) bit_ind_to_number[i] = i-(int)'0'+1;
    for(int i=(int)'A'; i<=(int)'F'; i++) bit_ind_to_number[i] = i-(int)'A'+11;
    //printf("KAROLUUUU %d\n\n",bit_ind_to_number['B']);
    bit_ind_to_number['x'] = 0;
    bit_ind_to_number['y'] = 1;
    itek = 1;
    while(sygnatura[itek]!='_'){
        deb printf("[1]sygnatura[%d]: %c \n",itek,sygnatura[itek]);
        if(sygnatura[itek++]=='y') bit_indeksu[itek_2++] = (bit_ind_to_number[(int)sygnatura[itek++]]);
        else bit_indeksu[itek_2++] = -(bit_ind_to_number[(int)sygnatura[itek++]]);
        itek++;
        Nx = min(bit_indeksu[itek_2-1],Nx);
        Ny = max(bit_indeksu[itek_2-1],Ny);
    }
    int pomocnicza[N];
    int jj,ii;
    for(ii=itek_2-1, jj=0; ii>=0; ii--, jj++) pomocnicza[jj] = bit_indeksu[ii];
    for(ii=itek_2-1; ii>=0; ii--) bit_indeksu[ii] = pomocnicza[ii];
    deb1 for(int i=0; i<10; i++) printf("bit_indeksu[%d]: %d\n",i,bit_indeksu[i]);
    Nx*=-1;
    deb1 printf("\nWYMIARY:\nNx=%d\nNy=%d\n",Nx,Ny);
    //Tworzenie tablic zależności w reguł negowania
    //zaleznosc[i][k] neguje bit x-owy na jezeli bit typu zaleznosc[i][0] (0 -x, 1 - y) jest zaleznosc[i][1] (tez 0,1)
    itek+=9;
    negacje_itek = 0;
    while(itek<strlen(sygnatura)){
        struct negacja neg;
        neg.typ_uzaleznionego = bit_ind_to_number[(int)sygnatura[itek]];
        deb2 printf("[2] sygnatura[%d]: %c \n",itek,sygnatura[itek]);
        itek++;
        neg.indeks_uzaleznionego = bit_ind_to_number[(int)sygnatura[itek]] - 1;
        deb2 printf("[3] sygnatura[%d]: %c \n",itek,sygnatura[itek]);
        itek+=2;
        neg.typ_uzalezniajacego = bit_ind_to_number[(int)sygnatura[itek]];
        deb2 printf("[4] sygnatura[%d]: %c \n",itek,sygnatura[itek]);
        itek++;
        neg.indeks_uzalezniajacego = bit_ind_to_number[(int)sygnatura[itek]] - 1;
        deb2 printf("[5] sygnatura[%d]: %c \n",itek,sygnatura[itek]);
        itek+=2;
        neg.wart_trigerujaca = bit_ind_to_number[(int)sygnatura[itek]] - 1;
        deb2 printf("[6] sygnatura[%d]: %c \n",itek,sygnatura[itek]);
        itek+=7;
        negacje[negacje_itek++] = neg;
    }

    if(s[0] == 'e'){
        deb printf("Encode:\n");
        scanf("%[^\n]%*c", punkt_wejscie);
        deb printf("x, y: %d %d\n",punkt_wejscie[7], punkt_wejscie[9]);
        int itek_3 = 7, itek_4 = 0, itek_5 = 0;
        while(punkt_wejscie[itek_3] != ','){
            deb printf("[y]%d\n", itek_4);
            y_s[itek_4++] = punkt_wejscie[itek_3++];
        }
        itek_3++;
        while(punkt_wejscie[itek_3] != ')'){
            deb printf("[x]%d\n",itek_5);
            x_s[itek_5++] = punkt_wejscie[itek_3++];
        }
        swtorz_x_y(itek_4,itek_5);
        for(int i=Nx+Ny; i>=0; i--){
            int pot2 = (1<<i);
            if(x-pot2>=0){
                x-=pot2;
                bity[i][0] = 1;
            }
            else bity[i][0] = 0;
            if(y-pot2>=0){
                y-=pot2;
                bity[i][1] = 1;
            }
            else bity[i][1] = 0;
        }
        swtorz_x_y(itek_4,itek_5);
        deb wypisz_bity(x,y);
        for(int i=0; i<negacje_itek; i++){
            //struct negacja neg = negacje[i];
            //deb printf("nagacje[%d]: Będę negował typu %d indeksu %d jeżeli typu %d indeksu %d ma wartosc %d\n",i,neg.typ_uzaleznionego,neg.indeks_uzaleznionego,neg.typ_uzalezniajacego,neg.indeks_uzalezniajacego,neg.wart_trigerujaca);
            wykonaj_negacje(i);
        }
        deb wypisz_bity(x,y);
        int ans = 0;
        deb printf("\n\nROBIMY ANSWER: \n\n");
        for(int i=0; i<itek_2; i++){
            if(bit_indeksu[i]<0){
                bit_indeksu[i]*=-1;
                bit_indeksu[i]--;
                ans+=bity[bit_indeksu[i]][0]*(1<<i);
                deb printf("[x] bit_indeksu[%d] = %d\n",i,bit_indeksu[i]);
                deb printf("[x] dodaje do ansa %d*%d\n\n",(1<<i),bity[bit_indeksu[i]][0]);
            }
            else{
                bit_indeksu[i]--;
                ans+=bity[bit_indeksu[i]][1]*(1<<i);
                deb printf("[y] bit_indeksu[%d] = %d\n",i,bit_indeksu[i]);
                deb printf("[y] dodaje do ansa %d*%d\n\n",(1<<i),bity[bit_indeksu[i]][1]);
            }
            deb2 printf("ans obecny: %d\n\n",ans);
        }
        printf("%d",ans);
    }
    else{
        deb printf("Decode:\n");
        scanf("\n%d",&indeks);
        int rozkladanie = indeks;
        for(int i=31; i>=0; i--){
            int pot2 = (1<<i);
            deb printf("siemano %d %d\n",pot2,rozkladanie);
            if(rozkladanie - pot2 >= 0){
                rozkladanie-=pot2;
                if(bit_indeksu[i]<0){
                    bit_indeksu[i]*=-1;
                    bit_indeksu[i]--;
                    bity[bit_indeksu[i]][0] = 1;
                    deb printf("[1] i=%d\n",i);
                }
                else{
                    bit_indeksu[i]--;
                    bity[bit_indeksu[i]][1] = 1;
                    deb printf("[2] i=%d\n",i);
                }
            }
            else{
                if(bit_indeksu[i]<0){
                    bit_indeksu[i]*=-1;
                    bit_indeksu[i]--;
                    bity[bit_indeksu[i]][0] = 0;
                    deb printf("[3] i=%d\n",i);
                }
                else{
                    bit_indeksu[i]--;
                    bity[bit_indeksu[i]][1] = 0;
                    deb printf("[4] i=%d\n",i);
                }
            }
        }
        for(int i=negacje_itek-1; i>=0; i--) wykonaj_negacje(i);
        deb printf("robimy x,y \n");
        int xx = 0, yy = 0;
        for(int i=0; i<32; i++){
            xx += bity[i][0]*(1<<i);
            yy += bity[i][1]*(1<<i);
        }
        deb wypisz_bity(xx,yy);
        printf("(y,x)=(%d,%d)",yy,xx);
    }
    return 0;
}
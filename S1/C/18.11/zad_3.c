#include <stdio.h>
#include <stdbool.h>
const int debug = 0;
const int debug2 = 0;
const int debug3 = 0;
#define deb if(debug)
#define deb2 if(debug2)
#define deb3 if(debug3)
#define N 11
struct blok{
    int id;
    int n;
    int m;
    bool structure[N][N];
    int najwyzszy[N];
    int najnizszy[N];
    int sumy_wierszy[N];
};
int n,m,num_blocks,tests,ans;
struct blok bloki[N];
int max(int a, int b){
    return (a > b) ? a : b;
}

struct blok blok_new(char structure[N][N], int n, int m, int id){
    struct blok b;
    b.id = id;
    b.n = n;
    b.m = m;
    for(int i=0; i<N; i++) b.sumy_wierszy[i] = 0;
    for(int j=0; j<N; j++){
        b.najnizszy[j] = n;
        b.najwyzszy[j] = -1;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(structure[i][j] == '#'){
                b.structure[i][j] = 1;
                b.najnizszy[j] = n-i-1;
                b.sumy_wierszy[n-i-1]++;
                if(b.najwyzszy[j] == -1) b.najwyzszy[j] = n-i-1;
            }
            else b.structure[i][j] = 0;
        }
    }
    return b;
}

void print_blok(struct blok b){
    printf("blok nr. %d:\n",b.id);
    printf("m: %d\nn: %d\n",b.m,b.n);
    for(int i=0; i<b.n; i++){
        for(int j=0; j<b.m; j++){
            printf("%d",b.structure[i][j]);
        }
        printf("\n");
    }
    printf("\nsumy_wierszy[]: \n");
    for(int j=0; j<b.n; j++) printf("%d: %d\n",j,b.sumy_wierszy[j]);
    printf("\nnajwyzszy[]: \n");
    for(int j=0; j<b.m; j++) printf("%d",b.najwyzszy[j]);
    printf("\nnajnizszy[]: \n");
    for(int j=0; j<b.m; j++) printf("%d",b.najnizszy[j]);
    printf("\n");
}
void solv(int permutacja[N], int itek , int najwyzsze[N],int sumy_wierszy[N]){
    deb2 printf("+++++++++++++++[WRZUCANIE] Będę wrzucał teraz %d blok\n",permutacja[itek]);
    struct blok wrzucany = bloki[permutacja[itek]];
    deb2{
        if(wrzucany.m>m){
            printf("[-] blok %d nie mieści się na szerokość ma szerokość %d a plansza ma %d\n",itek,wrzucany.m,m);
        } 
    }
    if(wrzucany.m>m) return;
    if(wrzucany.n>n) return;
    deb printf("wrzucany.m: %d |||| m: %d\n",wrzucany.m,m);
    for(int lewa_krawedz=0; lewa_krawedz<=m-wrzucany.m; lewa_krawedz++){
        deb2 printf("blok.id = %d ||||| Sprawdzam od krawedzy %d bede sprawdzal aż do %d krawedzi\n",wrzucany.id,lewa_krawedz,m-wrzucany.m);
        //wrzucanie do biezacego ustawienia bloki itek-owego t.że jego lewa krawędź bedzie na pozycji lewa_krawedz
        int y_zatrzymania = 0, najwyzsze_prim[N], sumy_wierszy_prim[N]; // pozycja y na ktorej zatrzyma sie blok
        bool wystaje = 0;
        for(int x=0; x<N; x++) najwyzsze_prim[x] = najwyzsze[x];
        for(int x=0; x<N; x++) sumy_wierszy_prim[x] = sumy_wierszy[x];
        //for(int x=lewa_krawedz; x<lewa_krawedz+wrzucany.m; x++) y_zatrzymania = max(najwyzsze_prim[x],y_zatrzymania); //zle bo blok zatrzymuje
        for(int x=lewa_krawedz; x<lewa_krawedz+wrzucany.m; x++){
            y_zatrzymania = max(y_zatrzymania,najwyzsze_prim[x] - wrzucany.najnizszy[x-lewa_krawedz]);
            deb2 printf("y_zatrzymania kandydat: %d - %d  = %d \n",najwyzsze_prim[x], wrzucany.najnizszy[x-lewa_krawedz], najwyzsze_prim[x] -wrzucany.najnizszy[x-lewa_krawedz] );
        }
        if(y_zatrzymania>n) return;
        deb2 printf("y_zatrzymania (pierwszy wiersz gdzie wystapi kolizja: %d\n",y_zatrzymania);
        for(int x=lewa_krawedz; x<lewa_krawedz+wrzucany.m; x++){
            deb2 printf("STARE: najwyzsze_prim[%d] = %d\n",x,najwyzsze_prim[x]);
            najwyzsze_prim[x] = max(najwyzsze_prim[x], wrzucany.najwyzszy[x-lewa_krawedz]+y_zatrzymania+1);
            deb2 printf("NOWE: najwyzsze_prim[%d] = %d\n",x,najwyzsze_prim[x]);
            //if(najwyzsze_prim[x]>=n) wystaje = 1; //wystaje poza plansze
            //deb2{
            //   if(najwyzsze_prim[x]>=n){
            //        printf("[-] Przy wrzucaniu %d bloku z od lewej od %d wystaje poza plansze na pozycji %d\n",itek,lewa_krawedz,x);
            //   }
            //}
        }
        for(int y=0; y<wrzucany.n; y++){
            deb3 printf("Obecne sumy_wierszy_prim[%d]: %d dodajemy wrzucany.sumy_wierszy[%d]: %d i mamy: %d\n",y+y_zatrzymania+1, sumy_wierszy_prim[y+y_zatrzymania+1], y, wrzucany.sumy_wierszy[y],sumy_wierszy_prim[y+y_zatrzymania+1]+wrzucany.sumy_wierszy[y]);
            if(y+y_zatrzymania+1 <= n) sumy_wierszy_prim[y+y_zatrzymania+1]+=wrzucany.sumy_wierszy[y];
            else wystaje = 1;
        }
        deb printf("wystaje: %d\n",wystaje);
        if(!wystaje && itek == num_blocks-1){
            int ans_cand = 0;
            for(int i=0; i<N; i++){
                if(sumy_wierszy_prim[i]==m) ans_cand++;
                deb2 printf("sumy_wierszy_prim[%d]: %d\n",i,sumy_wierszy_prim[i]);
            }
            ans = max(ans,ans_cand);
            //deb2 printf("Kończe sprawdzenie przypadku, wrzuciłem ostatni blok i siema\n");
            //return;
        }
        //if(wystaje) return;
        if(itek+1<num_blocks && !wystaje) solv(permutacja,itek+1,najwyzsze_prim,sumy_wierszy_prim);
        deb2 printf("SIEMANDERO KAROLU %d\n",lewa_krawedz);
    }
    deb2 printf("----------------[WRZUCANIE] Koniec wrzucania %d blok\n",itek);
}
int main(void){
    if(!scanf("%d%d%d",&m,&n,&num_blocks)) return 0;
    for(int czyt_bloki = 0; czyt_bloki<num_blocks; czyt_bloki++){
        int w,h;
        char structure[N][N];
        if(!scanf("%d%d",&w,&h)) return 0;
        for(int wiersze = 0; wiersze < h; wiersze++)if(!scanf("%s",structure[wiersze])) return 0;
        bloki[czyt_bloki] = blok_new(structure,h,w,czyt_bloki);
    }
    deb for(int i=0; i<num_blocks; i++) print_blok(bloki[i]);
    if(!scanf("%d",&tests)) return 0;
    while(tests--){
        //printf("tests %d\n",tests);
        ans = 0;
        int permutacja[N], najwyzsze[N],sumy_wierszy[N];
        for(int i=0; i<N; i++){najwyzsze[i] = 0; sumy_wierszy[i] = 0;}
        for(int i=0; i<num_blocks; i++) if(!scanf("%d",&permutacja[i])) return 0;
        solv(permutacja,0,najwyzsze,sumy_wierszy);
        printf("%d ",ans);
        deb2 printf("<- ANSWER\n======================================\n");

    }
    return 0;
}
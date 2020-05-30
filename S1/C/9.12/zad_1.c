#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define N 1000000
typedef struct Node {
    int count;
    struct Node* edges[26];
} Node;

Node trie[N];
char slowo[N];
int dl_slowa;

int dodaj_slowo(Node* vb, int ind_slowo){
    if(ind_slowo==dl_slowa) return vb->count;
    if(vb->edges[slowo[ind_slowo] - 'a']) //już był ten prefiks
        vb->edges[slowo[ind_slowo]-'a']->count++;
    else
        vb->edges[slowo[ind_slowo]-'a'] = (Node*)calloc(sizeof(Node),1);
    return dodaj_slowo(vb->edges[slowo[ind_slowo]-'a'], ind_slowo+1);
}

int main(void){
    char c;
    Node *root = (Node*)calloc(sizeof(Node),1);
    while((c=getchar())!=EOF){
        if(c!='\n'){
            slowo[dl_slowa++] = c;
        }
        else{
            printf("%d\n",dodaj_slowo(root,0));
            dl_slowa = 0;
        }
    }
    return 0;
}
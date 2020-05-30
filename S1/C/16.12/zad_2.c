#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const bool debug = 0;
#define deb if(debug)

int glob_count = -1;

typedef struct Node {
    int count,deep;
    int dir_name;
    struct Node* father;
    struct Node* edges[257];
} Node;

char command[1000], arg[1000];
int command_counter = 0, arg_counter = 0;
Node* stack[1000000];
Node* all_dirs[100000];
int stack_counter = 0;
struct Node* current;
/*Node* has_son(int ind){
    for(int sons=0; sons < current->count; sons++){
        if(current->edges[sons]->dir_name == ind) return current->edges[sons];
    }
    return NULL;
}*/
int arg_to_int(){
    int n=0;
    int pot10=1;
    for(int i=arg_counter-1; i>=0; i--){
        n+=(arg[i]-'0')*pot10;
        pot10*=10;
    }
    return n;
}
void add(){
    //if(current->count == 256) return;
    glob_count++;
    Node* new_dir = calloc(sizeof(Node),1);
    all_dirs[glob_count] = new_dir;
    current->edges[current->count]=new_dir;
    new_dir->deep = current->deep+1;
    new_dir->dir_name = glob_count;
    current->count++;
    new_dir->father = current;
    for(int i=0; i<arg_counter; i++) new_dir->dir_name[i] = arg[i];
}
int get_c(){
    return current->count;
}
int get_d(){
    return current->deep;
}
int get_s(){
    return glob_count-1;
}
void print(){
    if(arg[0]<'a'){
        printf("%d\n", arg_to_int());
    }
    else{
        switch(arg[0]):
            case 'c':
                printf("%d\n",get_c());
                break;
            case 'd':
                printf("%d\n",get_d());
                break;
            case 's':
                printf("%d\n",get_s());
                break;
            
    }
}

void move(int ind){
    if(arg[0]=='.'){
        current = current->father;
        return;
    }
    current = all_dirs[ind];
}
int main(void){
    char c;
    current = calloc(sizeof(Node),1);
    current->father = current;
    current->deep = 0;
    current->count = 0;
    current->dir_name = -1;
    while((c = getchar()) != EOF){
        arg_counter = 0, command_counter = 1;
        command[0] = c;
        while((c = getchar()) != ' ' && c != '\n' && c!='(') command[command_counter++] = c;
        if(c!='\n'){
            while((c = getchar()) == ' '){
                //nic
            }
            arg[arg_counter++] = c;
            while((c = getchar()) != '\n') arg[arg_counter++] = c;
        }

        switch(command[0]){
            case 'c':
                move();
                break;
            case 'm':
                add();
                break;
            case 'p':
                print();
                break;
            case 'w':
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const bool debug = 0;
#define deb if(debug)

typedef struct Node {
    int count;
    char dir_name[300];
    struct Node* father;
    struct Node* edges[300];
} Node;

char command[1000], arg[1000];
int command_counter = 0, arg_counter = 0;
Node* stack[100000];
int stack_counter = 0;
struct Node* current;
Node* has_son(){
    deb printf("debug0: %d \n", current->count);
    for(int sons=0; sons<current->count; sons++){
        bool flag = 1;
        for(int i=0; i<arg_counter; i++){
            deb printf("porównanko %c %c\n",arg[i],current->edges[sons]->dir_name[i]);
            if(arg[i]!=current->edges[sons]->dir_name[i]) flag = 0;
        }
        if(current->edges[sons]->dir_name[arg_counter]) flag = 0;
        if(flag) return current->edges[sons];
    }
    deb puts("nie ma syna");
    return NULL;
}
void add(){
    if(current->count == 256) return;
    if(has_son()) return;
    Node* new_dir = calloc(sizeof(Node),1);
    current->edges[current->count]=new_dir;
    deb printf("debug1: %d \n", current->count);
    current->count++;
    deb printf("debug2: %d \n", current->count);
    new_dir->father = current;
    for(int i=0; i<arg_counter; i++) new_dir->dir_name[i] = arg[i];
    deb printf("udało się dodać dira\n");
}

void print(){
    Node* current_print = current;
    stack_counter = 0;
    while(current_print!=current_print->father){
        stack[stack_counter++] = current_print;
        current_print = current_print->father;
    }
    stack[stack_counter] = current_print;
    for(int i=stack_counter; i>=0; i--){
        for(unsigned int l=0; l<strlen(stack[i]->dir_name); l++)
            printf("%c",stack[i]->dir_name[l]);
        printf("/");
    }
    printf("\n");
}

void move(){
    if(arg[0]=='.'){
        current = current->father;
        return;
    }
    Node* son = has_son();
    if(son) current = son;
}
int main(void){
    char c;
    current = calloc(sizeof(Node),1);
    current->father = current;
    while((c = getchar()) != EOF){
        arg_counter = 0, command_counter = 1;
        command[0] = c;
        while((c = getchar()) != ' ' && c != '\n') command[command_counter++] = c;
        if(c!='\n'){
            while((c = getchar()) == ' '){
                //nic
            }
            arg[arg_counter++] = c;
            while((c = getchar()) != '\n') arg[arg_counter++] = c;
        }
        deb printf("command:");
        for(int i=0; i<command_counter; i++) deb printf("%c",command[i]);
        deb printf("\narg:");
        for(int i=0; i<arg_counter; i++) deb printf("%c",arg[i]);
        deb printf("\n");

        deb printf("1count obecnego: %d\n",current->count);
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
        }
        deb printf("2count obecnego: %d\n",current->count);
    }

    return 0;
}
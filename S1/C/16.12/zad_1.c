#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define N 1000000
typedef struct Array2D {
    int width, height;
    int *t;
} Array2D;

void print(Array2D *array) {
    for (int y = 0; y < array->height; y++) {
        for (int x = 0; x < array->width; x++)
            printf(" %i",array->t[y*array->width+x]);
        printf("\n");
    }
    printf("\n\n");
}
void resize(Array2D *array, int width, int height){
    if(width*height==0){
        free(array->t);
        array->t = NULL;
        array->width = width;
        array->height = height;
        return;
    }
    //oba sie powiekszaja
    if(height >= array->height && width >= array->width){
        if(array->t) array->t = (int*)realloc(array->t,width*height*sizeof(int));
        else array->t = (int*)malloc(width*height*sizeof(int));
        for(int y = array->height-1; y>=0; y--){
            for(int x = array->width-1; x>=0; x--){
                    if(x<array->width && y<array->height) array->t[y*width+x] = array->t[y*array->width+x];
            }
        }
        for(int y = height-1; y>=0; y--){
            for(int x = width-1; x>=0; x--){
                    if(!(x<array->width && y<array->height)) array->t[y*width+x] = 0;
            }
        }
    }
    //tylko wysokosc sie zmniejsza
    if(height < array->height && width >= array->width){
        int delta = width - array->width;
        for(int y = height-1; y>=0; y--){
            for(int x = width-1; x>=0; x--){
                    if(x<width && y<height) array->t[y*array->width+x] = array->t[y*array->width+x-y*delta];
            }
        }
        for(int y = 0; y<height; y++){
            for(int x = 0; x<width; x++){
                    if(!(x<array->width && y<array->height)) array->t[y*width+x] = 0;
            }
        }
        if(array->t) array->t = (int*)realloc(array->t,width*height*sizeof(int));
        else array->t = (int*)malloc(width*height*sizeof(int));
    }
    //tylko szerokosc sie zmniejsza
    if(height >= array->height && width < array->width){
        int delta = array->width - width;
        for(int y = array->height-1; y>=0; y--){
            for(int x = array->width-1; x>=0; x--){
                if(x<width && y<height) array->t[y*array->width+x-y*delta] = array->t[y*array->width+x];
            }
        }
        for(int y = height-1; y>=0; y--){
            for(int x = width-1; x>=0; x--){
                    if(!(x<array->width && y<array->height)) array->t[y*width+x] = 0;
            }
        }
        if(array->t) array->t = (int*)realloc(array->t,width*height*sizeof(int));
        else array->t = (int*)malloc(width*height*sizeof(int));
    }
    //oba sie zmniejszaja
    if(height < array->height && width < array->width){
        int delta = array->width - width;
        for(int y = 0; y<height; y++){
            for(int x = 0; x<width; x++){
                array->t[y*width+x] = array->t[y*width+x-y*delta];
            }
        }
        if(array->t) array->t = (int*)realloc(array->t,width*height*sizeof(int));
        else array->t = (int*)malloc(width*height*sizeof(int));
    }
    array->width = width;
    array->height = height;
}

int main(void){
    Array2D a = {3,3, (int*)malloc(9*sizeof(int))};
    for(int i=0; i<9; i++) a.t[i] = i+1;
    print(&a);
    resize(&a, 4, 3); print(&a);
    resize(&a, 5, 2); print(&a);
    resize(&a, 2, 3); print(&a);
    resize(&a, 4, 5); print(&a);
    resize(&a, 4, 0); print(&a);
    resize(&a, 4, 1); print(&a);

    free(a.t);
    return 0;
}
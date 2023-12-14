#include <stdio.h>
#include <stdlib.h>

#define MWIDTH  100
#define MHEIGHT 100

int main(void) {
    FILE * fp;
    fp = fopen("example.txt","r");

    char points[8][13];
    int i,j;

    for(i=0; i<8; i++) {
        for(j=0; j<13; j++) {
            fscanf(fp,"%c",&points[i][j]);
        }
    }

    for(i=0; i<8; i++) {
        for(j=0; j<13; j++) {
            printf("%c",points[i][j]);
        }
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 141
#define HEIGHT 141

int checkForCharacter(char map[HEIGHT][WIDTH], int y, int x);

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");

    int mapNumber = 0, sum = 0;
    char mapChar[10] = {""}, singleMapCharacter, map[HEIGHT][WIDTH];
    bool validNumber = false;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fscanf(fp, "%c", &map[i][j]);
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        validNumber = false;
        for (int x = 0; x < WIDTH; x++) {
            if (isdigit(map[y][x])) {
                sprintf(mapChar, "%d%c", mapNumber, map[y][x]);
                mapNumber = atoi(mapChar);
                if (checkForCharacter(map, y, x) && mapNumber > 0) {
//                    printf("%d\n", mapNumber);
                    validNumber = true;
                }
            }

            if (map[y][x] == '.') {
                if(validNumber){
                    printf("%d\n", mapNumber);
                    sum += mapNumber;
                    validNumber = false;
                }
                mapNumber = 0;
            }
        }
    }

    printf("Total sum of part 1: %d", sum);

    fclose(fp);
    return 0;
}

int checkForCharacter(char map[HEIGHT][WIDTH], int y, int x) {
    int up[4] = {0, 1, -1};
    int down[4] = {0, 1, -1};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[y + up[i]][x + down[j]] == '#') {
                printf("%c Y: %d X: %d\t", map[y + up[i]][x + down[j]], (y + up[i]) +1, (x + down[j]) +1);
                return 1;
            }
        }
    }
    return 0;
}

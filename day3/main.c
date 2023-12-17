#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 141
#define HEIGHT 141

int checkForCharacter(char map[HEIGHT][WIDTH], int y, int x);

int sum = 0, mapNumber = 0;

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");

    char mapChar[10] = {""}, map[HEIGHT][WIDTH];
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
                if (mapNumber > 0 && (checkForCharacter(map, y, x) == 1)) {
                    validNumber = true;
                }
            }

            if (map[y][x] == '\n' || map[y][x] == '.' || map[y][x] == '*') {
                if (validNumber) {
                    sum += mapNumber;
                    validNumber = false;
                }
//                printf("X: %d\n", x);
                mapNumber = 0;
            }
        }
    }

    printf("Total sum of part 1: %d", sum);

    fclose(fp);
    return 0;
}

int checkForCharacter(char map[HEIGHT][WIDTH], int y, int x) {
    int up[3] = {-1, 0, 1};
    int down[3] = {-1, 0, 1};
    for (int yy = 0; yy < 3; yy++) {
        for (int xx = 0; xx < 3; xx++) {
            if (map[y + up[yy]][x + down[xx]] == '*') {
                printf("%c Y: %d X: %d \tnumber: %d sum: %d\n", map[y + up[yy]][x + down[xx]], (y + up[yy]) + 1,
                       (x + down[xx]) + 1, mapNumber, sum);
                return 1;
            }
        }
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int MAX_RED_BALLS = 12, MAX_GREEN_BALLS = 13, MAX_BLUE_BALLS = 14;

struct RGB {
    int red;
    int green;
    int blue;
};


char *trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char) *str))
        str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

struct RGB matchColour(struct RGB rgb, char *colour, char *number) {
    if (strcmp(colour, "red") == 0) {
        rgb.red = atoi(number) + rgb.red;
    } else if (strcmp(colour, "green") == 0) {
        rgb.green = atoi(number) + rgb.green;
    } else if (strcmp(colour, "blue") == 0) {
        rgb.blue = atoi(number) + rgb.blue;
    }
    return rgb;
}

bool validateMaxValues(struct RGB rgb) {
    bool valid = true;
    if (rgb.red > MAX_RED_BALLS) {
        return false;
    }
    if (rgb.blue > MAX_BLUE_BALLS) {
        return false;
    }
    if (rgb.green > MAX_GREEN_BALLS) {
        return false;
    }

    return valid;
}

int main() {
    int sumOfIds = 0, bufferLength = 400, gameId = 0;
    char delim[] = ":", wordCopy[50] = "", game[bufferLength], setCopy[50] = "";
    char *wordPtr, *word, *number, *colour, *set, *setPtr;

    FILE *filePointer;
    filePointer = fopen("file.txt", "r");

    struct RGB rgb = {
            0, 0, 0
    };

    while (fgets(game, bufferLength, filePointer)) {
        gameId++;
        for (set = strtok_r(game, ":;", &setPtr);
             set;
             set = strtok_r(NULL, ":;", &setPtr)) {
            *set = tolower(*set);
            strcpy(setCopy, set);
            char test2[100] = "";
            sprintf(test2, "game %d ", gameId);
            strcpy(setCopy, strtok(set, test2));
            printf("%s ", setCopy);
//            for (word = strtok_r(set, ",", &wordPtr);
//                 word;
//                 word = strtok_r(NULL, ",", &wordPtr)) {
//                word = trimwhitespace(word);
//
//                strcpy(wordCopy, word);
//                number = strtok(wordCopy, " ");
//                char test[strlen(number) + 1];
//
//                sprintf(test, "%s ", number);
//                colour = strtok(word, test);
//
//                rgb = matchColour(rgb, colour, number);
//            }
        }

        if (validateMaxValues(rgb)) {
            sumOfIds = gameId + sumOfIds;
        }


        rgb.red = 0;
        rgb.blue = 0;
        rgb.green = 0;
    }

//    printf("Sum of IDs: %d\n", sumOfIds);

    fclose(filePointer);
    return 0;
}
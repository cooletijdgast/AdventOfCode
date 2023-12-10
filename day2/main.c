#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_RED_BALLS 12
#define MAX_GREEN_BALLS 13
#define MAX_BLUE_BALLS 14

#define part1 true

struct RGB {
    int red, redMax;
    int green, greenMax;
    int blue, blueMax;
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
        if(rgb.red > rgb.redMax || rgb.redMax == 0)
            rgb.redMax = rgb.red;
    } else if (strcmp(colour, "green") == 0) {
        rgb.green = atoi(number) + rgb.green;
        if(rgb.green > rgb.greenMax || rgb.greenMax == 0)
            rgb.greenMax = rgb.green;
    } else if (strcmp(colour, "blue") == 0) {
        rgb.blue = atoi(number) + rgb.blue;
        if(rgb.blue > rgb.blueMax || rgb.blueMax == 0)
            rgb.blueMax = rgb.blue;
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

int part2Solve(struct RGB rgb) {
    int result;
    result = rgb.redMax * rgb.greenMax * rgb.blueMax;
    return result;
}

int main() {
    int sumOfIds = 0, bufferLength = 400, gameId = 0, part2Result = 0;
    char wordCopy[50] = "", game[bufferLength], setCopy[50] = "";
    char *wordPtr, *word, *number, *colour, *set, *setPtr;
    bool validSet = false;

    FILE *filePointer;
    filePointer = fopen("input.txt", "r");

    struct RGB rgb = {
            0, 0, 0, 0, 0, 0
    };

    while (fgets(game, bufferLength, filePointer)) {
        gameId++;
        validSet = false;
        for (set = strtok_r(game, ":", &setPtr);
             set;
             set = strtok_r(NULL, ";", &setPtr)) {
            *set = tolower(*set);
            strcpy(setCopy, set);

            char *token = strtok(set, ":");

            while (token) {
                char searchString[100];
                sprintf(searchString, "game %d ", gameId);

                char *substring = strstr(token, searchString);
                if (substring) {
                    memmove(substring, substring + strlen(searchString), strlen(substring + strlen(searchString)) + 1);
                }
                token = strtok(NULL, ":");
            }
            for (word = strtok_r(set, ",", &wordPtr);
                 word;
                 word = strtok_r(NULL, ",", &wordPtr)) {
                word = trimwhitespace(word);

                strcpy(wordCopy, word);
                number = strtok(wordCopy, " ");
                char numberDelimiter[strlen(number) + 1];

                sprintf(numberDelimiter, "%s ", number);
                colour = strtok(word, numberDelimiter);

                rgb = matchColour(rgb, colour, number);
            }

            if (!(validSet = validateMaxValues(rgb)) && part1) {
                rgb.red = 0;
                rgb.blue = 0;
                rgb.green = 0;
                break;
            }
            rgb.red = 0;
            rgb.blue = 0;
            rgb.green = 0;
        }
        part2Result += part2Solve(rgb);
        if (validSet) {
            sumOfIds = gameId + sumOfIds;
        }
        rgb.redMax = 0;
        rgb.blueMax = 0;
        rgb.greenMax = 0;
    }
    if(part1)
        printf("Part 1: sum of IDs: %d\n", sumOfIds);
    else
        printf("Part 2: sum of power of the sets: %d\n", part2Result);

    fclose(filePointer);
    return 0;
}

/**
 * Get highest value each game
 * Multiply all the highest value of each game with each other
 * Sum that total*/
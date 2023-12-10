#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

void part2();

int main() {
    FILE *fptr;
    fptr = fopen("text.txt", "r");

    char c;
    bool firstIsSet = false;
    int firstNumber = 0, secondNumber = 0;
    int total = 0;

    while ((c = fgetc(fptr)) != EOF) {
        if (isdigit(c)) {
            if (firstIsSet == false) {
                firstNumber = firstNumber * 10 + (c - '0');
            }
            secondNumber = 0;
            firstIsSet = true;
            secondNumber = secondNumber * 10 + (c - '0');
        }
        if (c == '\n') {
            char sumOfTwoNumbers[10];
            firstIsSet = false;
            sprintf(sumOfTwoNumbers, "%d%d", firstNumber, secondNumber);
            total += atoi(sumOfTwoNumbers);
            firstNumber = 0;
        }
    }
    printf("%d", total);
    fclose(fptr);
    return 0;
}


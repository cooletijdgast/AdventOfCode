#include <stdio.h>
#include <string.h>

void findAndReplace(char *input) {
    // Define a mapping of strings to their numeric equivalents
    const char *mapping[][2] = {
            {"one", "1"},
            {"two", "2"},
            {"three", "3"},
            {"four", "4"},
            {"five", "5"},
            // Add more mappings as needed
            {NULL, NULL} // End of the mapping
    };

    int length = strlen(input);

    // Iterate through the mapping and replace occurrences in the input string
    for (int i = 0; mapping[i][0] != NULL; i++) {
        char *pos = input;
        while ((pos = strstr(pos, mapping[i][0])) != NULL) {
            memcpy(pos, mapping[i][1], strlen(mapping[i][1]));
            pos += strlen(mapping[i][1]);
        }
    }
}

int main() {
    char input[] = "two1nine eightwothree abcone2threexyz xtwone3four 4nineeightseven2 zoneight234 7pqrstsixteen";

    printf("Original String: %s\n", input);

    findAndReplace(input);

    printf("Modified String: %s\n", input);

    return 0;
}

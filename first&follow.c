#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_PROD 10
#define MAX_LEN 10

int count, n = 0;
char first[MAX_PROD][MAX_LEN];
char follow[MAX_PROD][MAX_LEN];

char production[MAX_PROD][MAX_LEN];

void findFirst(char);
void findFollow(char);

int main() {
    printf("Enter the number of production rules: ");
    scanf("%d", &count);

    printf("Enter the production rules:\n");
    for (int i = 0; i < count; i++) {
        scanf("%s", production[i]);
    }

    // Calculate First sets
    for (int i = 0; i < count; i++) {
        findFirst(production[i][0]);
    }

    // Calculate Follow sets
    for (int i = 0; i < count; i++) {
        findFollow(production[i][0]);
    }

    // Display First sets
    printf("\nFirst Sets:\n");
    for (int i = 0; i < count; i++) {
        printf("First(%c) = {%s}\n", production[i][0], first[i]);
    }

    // Display Follow sets
    printf("\nFollow Sets:\n");
    for (int i = 0; i < count; i++) {
        printf("Follow(%c) = {%s}\n", production[i][0], follow[i]);
    }

    return 0;
}

void findFirst(char symbol) {
    int i, j;

    for (i = 0; i < count; i++) {
        if (production[i][0] == symbol) {
            if (!isupper(production[i][2])) {
                // If the next symbol is a terminal, add it to First set
                first[i][n++] = production[i][2];
            } else {
                // If the next symbol is a non-terminal, find its First set
                findFirst(production[i][2]);
            }
        }
    }
}

void findFollow(char symbol) {
    int i, j;

    if (production[0][0] == symbol) {
        // Add $ to Follow set of the start symbol
        strcat(follow[0], "$");
    }

    for (i = 0; i < count; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == symbol) {
                if (j == strlen(production[i]) - 1) {
                    // If the symbol is at the end of the production, find Follow set of the left-hand side
                    findFollow(production[i][0]);
                } else if (!isupper(production[i][j + 1])) {
                    // If the next symbol is a terminal, add it to Follow set
                    follow[i][strlen(follow[i])] = production[i][j + 1];
                } else {
                    // If the next symbol is a non-terminal, find its First set
                    int k = j + 1;
                    while (k < strlen(production[i]) && production[i][k] != '|') {
                        if (!isupper(production[i][k])) {
                            // If the next symbol is a terminal, add it to Follow set
                            follow[i][strlen(follow[i])] = production[i][k];
                            break;
                        } else {
                            // If the next symbol is a non-terminal, add its First set to Follow set
                            int index = 0;
                            while (production[i][k] != production[index][0]) {
                                index++;
                            }
                            strcat(follow[i], first[index]);
                            if (strchr(first[index], '#') == NULL) {
                                break;
                            } else {
                                k++;
                            }
                        }
                    }
                }
            }
        }
    }
}

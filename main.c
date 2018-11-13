#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    char* test_type = (char*)malloc(250 * sizeof(char));
    int year, test_number;

    printf("Subject:\n");
    fgets(test_type, 250 - 1, stdin);
    test_type[strlen(test_type) - 1] = '\0';

    printf("Year:\n");
    scanf("%d", &year);
    printf("Teest number:\n");
    scanf("%d", &test_number);

    if (strcmp(test_type, "sjl") == 0){
        sjl();
    }
    if (strcmp(test_type, "mat") == 0){
        mat(year, test_number);
    }
    if (strcmp(test_type, "anj") == 0){
        anj();
    }
    return 0;
}
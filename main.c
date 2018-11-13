#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    char* what = (char*)malloc(250 * sizeof(char));
    int rok, cislo_testu;

    printf("Subject:\n");
    fgets(what, 250 - 1, stdin);
    what[strlen(what) - 1] = '\0';

    printf("rok:\n");
    scanf("%d", &rok);
    printf("cislo testu:\n");
    scanf("%d", &cislo_testu);

    if (strcmp(what, "sjl") == 0){
        sjl();
    }
    if (strcmp(what, "mat") == 0){
        mat(rok, cislo_testu);
    }
    if (strcmp(what, "anj") == 0){
        anj();
    }
    return 0;
}
// Created by Susanka on 13. 11. 2018.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void anj(void){
    FILE* fr;
    FILE *fw;
    char* line = (char*)malloc(700 * sizeof(char));
    char* link = (char*)malloc(300 * sizeof(char));
    char* file = (char*)malloc(300 * sizeof(char));
    int lines = 0, i = 0;
    char* p_answers[15];                                                                                                 //dvojrozmerné pole = pole stringov, ako odpovede
    for (i = 0; i < 15; i++){
        p_answers[i] = (char*)malloc(300 * sizeof(char));
    }
    int num = 0;

    if ((fopen_s(&fr, "source.txt", "r") != 0) || fopen_s(&fw, "finalanj.txt", "w") != 0){                               //otváranie súboru
        printf("File 'source.txt' not found. Name a file 'source.txt' and then run a program.\n"
                       "Result will appear in file labeled 'finalsjl.txt'.\n");
        exit(1);
    }

    fprintf(fw, "private void createTest(){\n"                                                                           //vytvorenie testu
            "        List<Question> questions = new ArrayList<>();\n"
            "        long id = 1;\n"
            "        Question ");

    while (fgets(line, 700 - 1, fr) != NULL){
        line[strlen(line) - 1] = '\0';

        if (strstr(line, "https://") != NULL){
            num++;

            if ((num == 1) || (num == 9) || (num == 16) || (num == 24) || (num == 45) || (num == 56) || (num == 67) || (num == 75) || (num == 82)){
                strcpy(file, line);                                                                                      //nebolo možné zjednodušiť, lebo neexistuje nijaká postupnosť ako pri slovenčine
            }

            else{

                if (num != 2){                                                                                           //toto sa dáva za new quuestion, je to o jedno posunuté. čiže pri num 3 mi dáva odpovede pre num 2
                    for (i = 0; i < lines; i++){
                        if (i == lines - 1){
                            fprintf(fw, "\"%s\"", p_answers[i]);
                        }
                        else{
                            fprintf(fw, "\"%s\",", p_answers[i]);
                        }
                    }
                    fprintf(fw, "));\n"
                            "        questions.add(q);\n");

                    lines = 0;
                    for (i = 0; i < lines; i++){
                        strcpy(p_answers[i], "\0");
                    }
                }

                fprintf(fw,             "        q = new Question(id++,\n"
                        "                \"");
                fputs(file,fw);
                fprintf(fw, "\",\n");

                strcpy(link, line);
                fprintf(fw, "                \"");

                if (num >= 46 && num <= 74){                                                                             //Lukášova pripomienka, pri otázkach 41-67 má byť druhý linkový tring prázdny kvôli designu
                    ;
                }
                else{
                    fputs(link,fw);
                }

                if ((num <= 8) || ((num >23) && (num <= 44)) ){
                    fprintf(fw, "\",\n"
                            "                TYPE_AJ_ABCD,\n"
                            "                AJ_ABCD,\n"
                            "                Arrays.asList(");
                }

                if ((num <= 15) && ((num > 9))){
                    fprintf(fw, "\",\n"
                            "                TYPE_AJ_ABCD,\n"
                            "                AJ_ABC,\n"
                            "                Arrays.asList(");
                }

                if (  ((num > 15) && (num <= 23)) || ((num > 44) && (num <= 74)) || ( (num > 81) && (num <= 89) )){
                    fprintf(fw, "\",\n"
                            "                TYPE_AJ_RESPONSE,\n"
                            "                Collections.<String>emptyList(),\n"
                            "                Arrays.asList(");
                }
                if (num >74 && num <= 81){
                    fprintf(fw, "\",\n"
                            "                TYPE_AJ_COMBINED,\n"
                            "                AJ_AB,\n"
                            "                Arrays.asList(");
                }
            }
        }

        else{                                                                                                            //Ak riadok nezačína https, odpoveď sa pridá do poľa a zväčší sa počet odpovedí
            strcpy(p_answers[lines], line);
            lines++;
        }


        printf("%s\n", line);
    }

    if (num == 89){                                                                                                      //Posledný krát sa pole odpovedí musí prekopírovať ručne
        for (i = 0; i < lines; i++){
            if (i == lines - 1){
                fprintf(fw, "\"%s\"", p_answers[i]);
            }
            else{
                fprintf(fw, "\"%s\",", p_answers[i]);
            }
        }
        fprintf(fw, "));\n"
                "        questions.add(q);\n");
    }

    fprintf(fw, "    }");

    if (fclose(fr) == EOF || fclose(fw) == EOF){
        printf("Failed..\n");
    }
}
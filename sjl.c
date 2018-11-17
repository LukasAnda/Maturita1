// Created by TheZuzanka on 13. 11. 2018.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void sjl(void){
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

    if ((fopen_s(&fr, "source.txt", "r") != 0) || fopen_s(&fw, "finalsjl.txt", "w") != 0){                               //otváranie súboru
        printf("File 'source.txt' not found. Name a file 'source.txt' and then run a program.\n"
                       "Result will appear in file labeled 'finalsjl.txt'.\n");
        exit(1);
    }

    fprintf(fw, "private void createTest(){\n"                                                                           //vytvorenie testu
            "        List<Question> questions = new ArrayList<>();\n"
            "        long id = 1;\n"
            "        Question ");

    while (fgets(line, 700 - 1, fr) != NULL){                                                                           //whole line from file
        line[strlen(line) - 1] = '\0';

        if (strstr(line, "https://") != NULL){
            num++;

            if (num % 9 == 1){                                                                                           //(num == 1) || (num == 10) || (num == 19) || (num == 28) || (num == 37) || (num == 46) || (num == 55) || (num == 64)
                strcpy(file, line);                                                                                      // first and every 9th starts a new document = text, which belong to the questions
            }

            else{

                if (num != 2){                                                                                           //goes at the end of function --> function n, writing for n-1
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
                fputs(link,fw);
                if (num % 9 >= 2 && num % 9 <= 6){
                    fprintf(fw, "\",\n"
                            "                TYPE_SJL_ABCD,\n"
                            "                SJL_ABCD,\n"
                            "                Arrays.asList(");
                }

                if (num % 9 >= 7 || num % 9 == 0){
                    fprintf(fw, "\",\n"
                            "                TYPE_SJL_RESPONSE,\n"
                            "                Collections.<String>emptyList()\n"
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

    if (num == 72){                                                                                                      //Posledný krát sa pole odpovedí musí prekopírovať ručne
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
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char* what = (char*)malloc(250 * sizeof(char));
    int rok, cislo_testu;
    void sjl(void);
    void mat(int rok, int cislo_testu);
    void anj(void);

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

    while (fgets(line, 700 - 1, fr) != NULL){
        line[strlen(line) - 1] = '\0';

        if (strstr(line, "https://") != NULL){
            num++;

            if (num % 9 == 1){                                                                                           //(num == 1) || (num == 10) || (num == 19) || (num == 28) || (num == 37) || (num == 46) || (num == 55) || (num == 64)
                strcpy(file, line);                                                                                      // prvá a potom každá deviata otázka je prvou otázkou nového dokumentu, trba pridať link, ostatné majú rovnaký ako ten predchádzajúci
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

void mat(int rok, int cislo_testu){
    FILE* fr;
    FILE *fw;
    char* line = (char*)malloc(700 * sizeof(char));
    char* link = (char*)malloc(300 * sizeof(char));
    int lines = 0, i = 0;
    int num = 0;

    if ((fopen_s(&fr, "source.txt", "r") != 0) || fopen_s(&fw, "finalmat.txt", "w") != 0){
        printf("File 'source.txt' not found. Name a file 'source.txt' and then run a program.\n"
                       "Result will appear in file labeled 'finalmat.txt'.\n");
        exit(1);
    }

    fprintf(fw, "private void pridajMatTest%d(FirebaseFirestore db){\n"
            "        List<Question> questions = new ArrayList<>();\n"
            "        long id = 1;\n"
            "        Question", rok);

    while(fgets(line, 700, fr) != NULL){
        line[strlen(line) - 1] = '\0';
        printf("%s\n", line);
        num++;

        if (num % 2 != 0){
            fprintf(fw, "        q = new Question(id++,\n"
                    "                \"\",\n"
                    "                \"%s\",\n", line);
        }
        else{
            if(num <= 40){
                fprintf(fw, "                TYPE_MAT_RESPONSE,\n"
                        "                Collections.<String>emptyList(),\n"
                        "                Arrays.asList(\"%s\"));\n"
                        "        questions.add(q);\n", line);
            }
            else{
                fprintf(fw, "                TYPE_MAT_ABCD,\n"
                        "                MAT_ABCD,\n"
                        "                Arrays.asList(\"%s\"));\n"
                        "        questions.add(q);\n", line);
            }
        }
    }

    fprintf(fw, "        Test test = new Test(\"Matematika %d\", \"%d\", \"mat\", questions);\n"
            "        db.collection(\"test\").document(test.getName())"
            "                .set(test)\n"
            "                .addOnSuccessListener(new OnSuccessListener<Void>() {\n"
            "                    @Override\n"
            "                    public void onSuccess(Void aVoid) {\n"
            "                        Log.d(\"TAG\", \"DocumentSnapshot successfully written!\");\n"
            "                    }\n"
            "                })\n"
            "                .addOnFailureListener(new OnFailureListener() {\n"
            "                    @Override\n"
            "                    public void onFailure(@NonNull Exception e) {\n"
            "                        Log.w(\"TAG\", \"Error writing document\", e);\n"
            "                    }\n"
            "                });\n"
            "}", rok, cislo_testu);

    if (fclose(fr) == EOF || fclose(fw) == EOF){
        printf("Failed..\n");
    }
}

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
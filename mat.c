// Created by TheZuzanka on 13. 11. 2018.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void mat(int rok, int cislo_testu){
    FILE* fr;
    FILE *fw;
    char* line = (char*)malloc(700 * sizeof(char));
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
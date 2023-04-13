#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int writeMatrixToDotFile(char* filePath) {
    FILE* dotFile = fopen("graph.dot", "w");
    if (dotFile == NULL) {
        return -1;
    }

    FILE* matrixFile = fopen(filePath, "r");
    if (matrixFile == NULL) {
        return -1;
    }

    fprintf(dotFile, "digraph Matrix {\n");
    int currentRow = 1;
    int currentColumn = 1;
    int countOfColumns = 0;

    while (!feof(matrixFile)) {
        int currentWeight = 0;
        int isEof = fscanf(matrixFile, "%d", &currentWeight);
        if (isEof == EOF) {
            fprintf(dotFile, "}");
            fclose(dotFile);
            fclose(matrixFile);
            return countOfColumns == currentColumn && countOfColumns == currentRow ? 0 : -1;
        }
        if (isEof == 0) {
            fclose(dotFile);
            fclose(matrixFile);
            return -1;
        }
        if (currentWeight != 0) {
            fprintf(dotFile, "    %d -> %d[label=%d];\n", currentRow, currentColumn, currentWeight);
        }

        isEof = fgetc(matrixFile);

        if (isEof == '\n') {
            ++currentRow;
            countOfColumns = currentColumn;
            currentColumn = 0;
        }
        else if (isEof == EOF) {
            fprintf(dotFile, "}");
            fclose(dotFile);
            fclose(matrixFile);
            return currentColumn == countOfColumns && currentRow == countOfColumns ? 0 : -1;
        }
        ++currentColumn;
    }
    fprintf(dotFile, "}");
    fclose(dotFile);
    fclose(matrixFile);
    return currentRow == countOfColumns ? 0 : -1;
}

bool test(void) {
    char* filePath= "test.txt";
    int errorCode = writeMatrixToDotFile(filePath);
    if (errorCode == -1) {
        return false;
    }
    FILE* dotFile = fopen("graph.dot", "r");
    if (dotFile == NULL) {
        return false;
    }
    char buffer[50] = "";
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool firstLine = !strcmp(buffer, "digraph Matrix {");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool secondLine = !strcmp(buffer, "    1 -> 2[label=2];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool thirdLine = !strcmp(buffer, "    2 -> 3[label=3];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool fourthLine = !strcmp(buffer, "    3 -> 4[label=4];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool fifthLine = !strcmp(buffer, "    3 -> 6[label=8];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool sixthLine = !strcmp(buffer, "    4 -> 6[label=7];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool seventhLine = !strcmp(buffer, "    5 -> 4[label=5];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool eighthLine = !strcmp(buffer, "    6 -> 1[label=6];");
    fscanf(dotFile, "%[^\n]", buffer);
    fgetc(dotFile);
    bool ninthLine = !strcmp(buffer, "    6 -> 2[label=1];");
    fclose(dotFile);
    remove("graph.dot");

    return firstLine && secondLine && thirdLine && fourthLine && fifthLine && sixthLine && seventhLine && eighthLine && ninthLine;
}

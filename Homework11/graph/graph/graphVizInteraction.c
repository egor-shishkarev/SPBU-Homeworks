#include <stdio.h>

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

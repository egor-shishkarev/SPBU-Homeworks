#include <stdio.h>
#include <malloc.h>

int main(void) {
    FILE* file = fopen("text.txt", "r");
    int currentLine = 1;
    while (!feof(file)) {
        char* buffer = calloc(1000, sizeof(char));
        if (fscanf(file, "%s", buffer) == -1) {
            free(buffer);
            break;
        }
    }
    
    return 0;
}

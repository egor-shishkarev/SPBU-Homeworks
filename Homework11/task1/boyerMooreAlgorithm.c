#include "boyerMooreAlgorithm.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int* createArrayOfPrefixFunction(const char* string, int* errorCode) {
    int* offset = calloc(strlen(string), sizeof(int));
    if (offset == NULL) {
        *errorCode = -1;
        return NULL;
    }
    int j = 0;
    int i = 1;
    while (i < strlen(string)) {
        if (string[j] == string[i]) {
            offset[i] = j + 1;
            ++i;
            ++j;
        } else {
            if (j == 0) {
                offset[i] = 0;
                ++i;
            } else {
                j = offset[j - 1];
            }
        }
    }
    return offset;
}

int findString(const char* text,const char* string, int* offset) {
    int textIndex = 0;
    int offsetIndex = 0;
    const int lengthOfText = (int)strlen(text);
    const int lengthOfString = (int)strlen(string);
    while (textIndex < lengthOfText) {
        if (text[textIndex] == string[offsetIndex]) {
            ++textIndex;
            ++offsetIndex;
            if (offsetIndex == lengthOfString) {
                return textIndex - lengthOfString + 1;
            }
        } else {
            if (offsetIndex > 0) {
                offsetIndex = offset[offsetIndex - 1];
            } else {
                ++textIndex;
                if (textIndex == lengthOfText) {
                    return textIndex + 1;
                }
            }
        }
    }
    return -1;
}
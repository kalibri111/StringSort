//
// Created by kalibri on 09.09.2020.
//

#include <stdlib.h>
#include "filestuff.h"


int fileRowsCount(FILE* file) {
    int count_ = 0;
    while (feof(file)) {
        char cur_char = (char)fgetc(file);
        if (!cur_char) {
            count_++;
        }
    }
    return count_;
}

void fileToArr(FILE* file, char** buffer) {
    char* ptr_string = calloc(MAX_ROW_SIZE, sizeof('a'));
    int i = 0;
    int n = 0;

    while (feof(file)) {
        char cur_char = (char)fgetc(file);
        if (cur_char && i < MAX_ROW_SIZE) {
            ptr_string[i++] = cur_char;
        } else {
            buffer[n++] = ptr_string;
            ptr_string = calloc(MAX_ROW_SIZE, sizeof('a'));
            i = 0;
        }
    }
}

int arrToFile(FILE* file, char** arrOfStrings, int nStrings) {
    for (int i = 0; i < nStrings; ++i) {
        if (!fputs(arrOfStrings[i], file)) {
            return 0;
        }
    }
    return 1;
}

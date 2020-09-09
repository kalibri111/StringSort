//
// Created by kalibri on 09.09.2020.
//

#ifndef STRINGSORT_FILESTUFF_H
#define STRINGSORT_FILESTUFF_H

#endif //STRINGSORT_FILESTUFF_H

#include <stdio.h>

#define MAX_ROW_SIZE 100

int fileRowsCount(FILE* file);

void fileToArr(FILE* file, char** buffer);

int arrToFile(FILE* file, char** arrOfStrings, int nStrings);

#include <stdio.h>
#include "filestuff.h"
#include "stringsort.h"

int main(int argC, const char* argV[]) {
    FILE* inputFile = fopen(*(argV + 1), "r");
    int nRows = fileRowsCount(inputFile);

    char* fileRows[nRows];

    fileToArr(inputFile, fileRows);

    fclose(inputFile);

    FILE* outputFile = fopen("out.txt", "w");

    sort(fileRows, nRows);

    if(arrToFile(outputFile, fileRows, nRows)) {
        printf("Successfully sorted in new file");
    } else {
        printf("Something went wrong");
    }
}

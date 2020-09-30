#include <stdio.h>
#include "headers/stringsort.h"
#include "tests/tests.h"


const char* RESULT_FILEPATH = "../out.txt";


int main(int argC, const char* argV[]) {
#ifdef DEBUG
    run_all_tests();
#else
    const char* file_name = *(argV + 1);
    if(file_name == NULL) {
        fprintf(stderr, "Input filename required");
        return EXIT_FAILURE;
    }

    /*-----------------reading block----------------------*/
    FILE* input_file = fopen(file_name, "r");

    size_t file_size  = getFileSize(input_file) + 1;  // будем выделять на один символ про запас для \n в конце
    char* buffer      = newBufFromFile(input_file, file_size);
    size_t rows_count = evaluateBuffer(buffer, file_size, '\n', '\0');

    fclose(input_file);
    /*----------------------------------------------------*/

    strview_t* index = newIndex(buffer, rows_count, file_size);
    if (index == NULL) {
        fprintf(stderr, "Invalid file format");
        return EXIT_FAILURE;
    }

    sort_forward(index, rows_count);
    indexToFile(RESULT_FILEPATH, index, rows_count);
    
    sort_backward(index, rows_count);
    indexToFile(RESULT_FILEPATH, index, rows_count);

    buffToFile(RESULT_FILEPATH, buffer, file_size);

    destroyIndex(index);
    destroyBuffer(buffer);
    printf("Successfully sorted in new file %s", RESULT_FILEPATH);
#endif
}

#include <stdio.h>
#include "stringsort.h"
#include "tests.h"


const char* RESULT_FILEPATH = "../out.txt";


int main(int argC, const char* argV[]) {
#ifdef DEBUG
    run_all_tests();
#else
    const char* file_name_ = *(argV + 1);

    size_t file_size  = getFileSize(file_name_) + 1;  // будем выделять на один символ про запас для \n
    char* buffer      = newBufFromFile(file_name_, file_size);
    size_t rows_count = evaluateBuffer(buffer, file_size, '\n', '\0');

    struct strview* index = newIndex(buffer, rows_count, file_size);

    sort_forward(index, rows_count);
    indexToFile(RESULT_FILEPATH, index, rows_count);
    
    sort_backward(index, rows_count);
    indexToFile(RESULT_FILEPATH, index, rows_count);

    buffToFile(RESULT_FILEPATH, buffer, file_size);

    free(buffer);
    free(index);
    printf("Successfully sorted in new file %s", RESULT_FILEPATH);
#endif
}

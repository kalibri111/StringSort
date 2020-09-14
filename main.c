#include <stdio.h>
#include "stringsort.h"
#include "tests.h"

//#define DEBUG

char* RESULT_FILEPATH = "/home/kalibri/MIPT/1_sem/Dedinsky/StringSort/out.txt";


int main(int argC, char* argV[]) {
#ifdef DEBUG
    run_all_tests();
#else
    char* file_name_ = *(argV + 1);
    int file_size_ = getFileSize(file_name_);
    size_t rows_count_ = fileRowsCount(file_name_);

    char file_buffer_[file_size_];

    struct strview index_[rows_count_];

    fileToBuff(file_name_, file_buffer_, file_size_);
    makeIndex(index_, file_buffer_, rows_count_);

    sort_forward(index_, rows_count_);
    indexToFile(RESULT_FILEPATH, index_, rows_count_);
    
    sort_backward(index_, rows_count_);
    indexToFile(RESULT_FILEPATH, index_, rows_count_);

    printf("Successfully sorted in new file out.txt");
#endif
}

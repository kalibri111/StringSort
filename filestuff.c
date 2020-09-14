//
// Created by kalibri on 09.09.2020.
//
#include "filestuff.h"
#include <sys/stat.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>




int getFileSize(char* file_name) {
    FILE* file = fopen(file_name, "rb");
    struct stat buff;
    fstat(fileno(file), &buff);
    fclose(file);
    int t = buff.st_size;
    return buff.st_size;
}


int fileRowsCount(char* file_name) {
    FILE* file = fopen(file_name, "rb");
    int count_ = 0;
    char cur_char = (char)fgetc(file);
    while (cur_char > 0) {
        cur_char = (char)fgetc(file);
        if (cur_char == '\n') {
            count_++;
        }
    }
    fclose(file);
    return count_;
}


void fileToBuff(char* file_name, char* buffer, size_t file_size) {
    FILE* file = fopen(file_name, "rb");
    fread(buffer, sizeof(char), file_size, file);

    for (int i = 0; i < file_size; ++i) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
        }
    }
    fclose(file);
}


void indexToFile(char* file_name, struct strview* index, size_t index_size) {
    FILE* file = fopen(file_name, "a+");
    for (int i = 0; i < index_size; ++i) {
        fputs(index[i].str, file);
        fputc('\n', file);
    }
    fputs("----------------------------------------------\n", file);
    fclose(file);
}

void makeIndex(struct strview* index_buffer, char* file_buffer, size_t index_size) {
    index_buffer[0].str = file_buffer;
    index_buffer[0].strlen = strlen(file_buffer);

    for (int i = 1; i < index_size; ++i) {
//        char* c = index_buffer[i - 1].str + index_buffer[i - 1].strlen + 1;
        index_buffer[i].str = index_buffer[i - 1].str + index_buffer[i - 1].strlen + 1;
        index_buffer[i].strlen = strlen(index_buffer[i].str);
    }
}

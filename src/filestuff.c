//
// Created by kalibri on 09.09.2020.
//
#include "../headers/filestuff.h"
#include <sys/stat.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>


int getFileSize(const char* file_name) {
    FILE* file = fopen(file_name, "rb");
    struct stat buff = {};
    stat(file_name, &buff);
    fclose(file);
    return buff.st_size;
}

int evaluateBuffer(char* buffer, size_t size, char orig, char new) {
    int count_ = 0;
    for (int i = 0; i < size; ++i) {
        if (buffer[i] == orig) {
            ++count_;
            buffer[i] = new;
        }
    }
    return count_;
}

void destroyBuffer(char* buffer) {
    free(buffer);
}

char* newBufFromFile(const char* file_name, size_t buf_size) {
    char* buffer = malloc(sizeof(char) * (buf_size));
    FILE* file = fopen(file_name, "rb");
    fread(buffer, sizeof(char), buf_size, file);
    fclose(file);
    buffer[buf_size - 1] = '\n';
    return buffer;
}

void indexToFile(const char* file_name, strview_t* index, size_t index_size) {
    FILE* file = fopen(file_name, "a+");
    for (int i = 0; i < index_size; ++i) {
        fputs(index[i].str, file);
        fputc('\n', file);
    }
    fputs("----------------------------------------------\n", file);
    fclose(file);
}

void destroyIndex(strview_t* index) {
    free(index);
}

enum term_type termType(const char* file_buffer, size_t buffer_size) {
    enum term_type term_t;

    int zero_counter = 0;
    for (int i = 0; i < buffer_size; ++i) {
        if (file_buffer[i] == '\0') {
            ++zero_counter;
        } else {
            zero_counter = 0;
        }
    }

    if (zero_counter == 0 || zero_counter > 2) {
        return INVALID;
    }

    if (buffer_size >= 2) {
        if (file_buffer[buffer_size - 1] == '\0' && file_buffer[buffer_size - 2] == '\0') {
            term_t = DOUBLE_ZERO;
        } else if (file_buffer[buffer_size - 1] == '\0') {
            term_t = SINGLE_ZERO;
        } else {
            term_t = INVALID;
        }
    } else {
        if (file_buffer[buffer_size - 1] == '\0') {
            term_t = SINGLE_ZERO;
        } else {
            term_t = INVALID;
        }
    }
    return term_t;
}

strview_t* newIndex(char* file_buffer, size_t index_size, size_t buffer_size) {
    strview_t* index_buffer = malloc(index_size * sizeof(strview_t));

    enum term_type term_t = termType(file_buffer, buffer_size);

    index_buffer[0].str = file_buffer;

    size_t j = 1;

    if (term_t == DOUBLE_ZERO) {
        for (int i = 0; i < buffer_size - 1; ++i) {
            if (file_buffer[i] == '\0' && file_buffer[i + 1] != '\0') {
                index_buffer[j].str = &(file_buffer[i]) + 1;
                index_buffer[j - 1].strlen = index_buffer[j].str - index_buffer[j - 1].str - 1;
                ++j;
            } else if (file_buffer[i] == '\0' && file_buffer[i + 1] == '\0') {
                index_buffer[j - 1].strlen = &file_buffer[i] - index_buffer[j - 1].str;
            }
        }
    } else if (term_t == SINGLE_ZERO) {
        for (int i = 0; i < buffer_size; ++i) {
            if (file_buffer[i] == '\0' && i != buffer_size - 1) {
                index_buffer[j].str = &(file_buffer[i]) + 1;
                index_buffer[j - 1].strlen = index_buffer[j].str - index_buffer[j - 1].str - 1;
                ++j;
            } else if (file_buffer[i] == '\0' && i == buffer_size - 1) {
                index_buffer[j - 1].strlen = &file_buffer[i] - index_buffer[j - 1].str;
            }
        }
    } else if (term_t == INVALID) {
        return NULL;
    }

    return index_buffer;
}

void buffToFile(const char* file_name, char* buffer, size_t buffer_size) {
    FILE* file = fopen(file_name, "a+");
    evaluateBuffer(buffer, buffer_size, '\0', '\n');
    fputs(buffer, file);
    fputs("----------------------------------------------\n", file);
    fclose(file);
}

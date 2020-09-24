//
// Created by kalibri on 09.09.2020.
//

#ifndef STRINGSORT_FILESTUFF_H
#define STRINGSORT_FILESTUFF_H

#endif //STRINGSORT_FILESTUFF_H

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>


/*
 * тип терминирования файла:
 * DOUBLE_ZERO - .....\0\0
 * SINGLE_ZERO - .....\0
 * INVALID     - .....
 * */
enum term_type {DOUBLE_ZERO, SINGLE_ZERO, INVALID};

typedef struct strview
{
    size_t strlen;
    char* str;
} strview_t;

/*
 * аллоцирует заданное количество структур
 * */
struct strview* newIndexPull(size_t n_count);

/*
 * проверяет тип терминирования файла
 * возвращает term_type
 * */
enum term_type termType(const char* file_buffer, size_t buffer_size);

/*
 * создает массив strview, ставит указатель на начало каждого слова
 * необходимо вызывать free() после использования
 * возвращает NULL если termType от buffer INVALID
 * */
struct strview* newIndex(char* file_buffer, size_t index_size, size_t buffer_size);

void destroyIndex(strview_t* index);

/*
 * возвращает размер файла в байтах
 * */
int getFileSize(const char* file_name);

/*
 * подсчет количества строк в файле
 * */
int evaluateBuffer(char* buffer, size_t size, char orig, char new);

/*
 * запись файла в массив построчно, строки разделены \0
 * необходимо вызывать free() после использования
 * */
char* newBufFromFile(const char* file_name, size_t buf_size);

void destroyBuffer(char* buffer);

/*
 * запись из массивов в файл построчно
 * */
void indexToFile(const char* file_name, struct strview* index, size_t index_size);

void buffToFile(const char* file_name, char* buffer, size_t buffer_size);

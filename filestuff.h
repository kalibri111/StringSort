//
// Created by kalibri on 09.09.2020.
//

#ifndef STRINGSORT_FILESTUFF_H
#define STRINGSORT_FILESTUFF_H

#endif //STRINGSORT_FILESTUFF_H

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

#define MAX_ROW_SIZE 100


struct strview
{
    size_t strlen;
    char* str;
};

/*
 * создает массив strview, ставит указатель на начало каждого слова
 * */
void makeIndex(struct strview* index_buffer, char* file_buffer, size_t index_size);

/*
 * возвращает размер файла в байтах
 * */
int getFileSize(char* file_name);

/*
 * подсчет количества строк в файле
 * */
int fileRowsCount(char* file_name);

/*
 * запись файла в массив построчно, строки разделены \0
 * */
void fileToBuff(char* file_name, char* buffer, size_t file_size);

/*
 * запись из массивов в файл построчно
 * */
void indexToFile(char* file_name, struct strview* index, size_t index_size);

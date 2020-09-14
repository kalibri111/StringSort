//
// Created by kalibri on 09.09.2020.
//

#ifndef STRINGSORT_STRINGSORT_H
#define STRINGSORT_STRINGSORT_H

#endif //STRINGSORT_STRINGSORT_H


#include <stdlib.h>
#include "filestuff.h"
/*
 * лексикографическая сортировка на месте
 * */
void sort_forward(struct strview* index_buffer, size_t buffer_size);

/*
 * лексикографическая сортировка на месте в обратном порядке
 * */
void sort_backward(struct strview* index_buffer, size_t buffer_size);

/*
 * Сравнение строк символ за символом,
 * соответствует <string.h>
 * */
int forward_strcmp(const struct strview* str1, const struct strview* str2);

/*
 * сравнение строк в обратном порядке
 * */
int reversed_strcmp(const struct strview* str1, const struct strview* str2);

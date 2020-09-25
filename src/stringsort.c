//
// Created by kalibri on 09.09.2020.
//

#include "../headers/stringsort.h"
#include <ctype.h>

int common_strcmp(const void* str1, const void* str2, size_t str1_begin, size_t str2_begin, int step) {
    char* lhs_str = ((const strview_t*)str1)->str + str1_begin;
    char* rhs_str = ((const strview_t*)str2)->str + str2_begin;

    while (*lhs_str && *rhs_str) {
//        передвигаем указатель вперед, пока не найдем букву
        while (!isalpha(*lhs_str)) {
            lhs_str += step;
        }
        while (!isalpha(*rhs_str)) {
            rhs_str += step;
        }
//        сравниваем
        if (*lhs_str != *rhs_str) {
            return *lhs_str - *rhs_str;
        }
        lhs_str += step;
        rhs_str += step;
    }
    return 0;
}

int forward_strcmp(const void* str1, const void* str2) {
    return common_strcmp(str1, str2, 0, 0, 1);
}

int reversed_strcmp(const void* str1, const void* str2) {
    size_t str1_len = ((const strview_t*)str1)->strlen;
    size_t str2_len = ((const strview_t*)str2)->strlen;
    return common_strcmp(str1, str2, str1_len, str2_len, -1);
}

/*
 * quicksort по схеме Хоара
 * */
int partition(strview_t* arrOfStrings, int leftIndex, int rightIndex,
        int (*comp)(const void* str1, const void* str2)) {
    int l_index = leftIndex;
    int r_index = rightIndex;
    strview_t* sample = &arrOfStrings[(l_index + r_index) / 2];

    while (l_index <= r_index) {
        while (comp(&arrOfStrings[l_index], sample) < 0) {
            ++l_index;
        }
        while (comp(&arrOfStrings[r_index], sample) > 0) {
            --r_index;
        }
        if (l_index >= r_index) {
            break;
        }

        strview_t tmp         = arrOfStrings[l_index];
        arrOfStrings[l_index] = arrOfStrings[r_index];
        arrOfStrings[r_index] = tmp;

        l_index++;
        r_index--;
    }
    return r_index;
}

void quicksort(strview_t* array, int l_index, int r_index,
               int (*comp)(const void* str1, const void* str2)) {
    if (l_index < r_index) {
        int sample_index = partition(array, l_index, r_index, comp);
        quicksort(array, l_index, sample_index, comp);
        quicksort(array, sample_index + 1, r_index, comp);
    }
}

void sort(strview_t* arrOfStrings, int nStrings,
        int (*comp)(const void* str1, const void* str2)) {
    quicksort(arrOfStrings, 0, nStrings - 1, comp);
}

void sort_forward(strview_t* index_buffer, size_t buffer_size) {
    sort(index_buffer, buffer_size, forward_strcmp);
//    qsort(index_buffer, buffer_size, sizeof(strview_t), forward_strcmp);
}

void sort_backward(strview_t* index_buffer, size_t buffer_size) {
//    sort(index_buffer, buffer_size, reversed_strcmp);
    qsort(index_buffer, buffer_size, sizeof(strview_t), reversed_strcmp);
}


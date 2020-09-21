//
// Created by kalibri on 09.09.2020.
//

#include "stringsort.h"
#include <ctype.h>


int forward_strcmp(const void* str1, const void* str2) {
    char* lhs_str = ((const struct strview*)str1)->str;
    char* rhs_str = ((const struct strview*)str2)->str;

    while (*lhs_str && *rhs_str) {
//        передвигаем указатель, пока не найдем букву
        while (!isalpha(*lhs_str)) {
            ++lhs_str;
        }
        while (!isalpha(*rhs_str)) {
            ++rhs_str;
        }
//        сравниваем
        if (*lhs_str > *rhs_str) {
            return 1;
        } else if (*lhs_str < *rhs_str) {
            return -1;
        }
        ++lhs_str;
        ++rhs_str;
    }
    return 0;
}

int reversed_strcmp(const void* str1, const void* str2) {
//    идем с конца
    const struct strview* str1_v = (const struct strview*)str1;
    const struct strview* str2_v = (const struct strview*)str2;

    char* lhs_str = str1_v->str + str1_v->strlen - 1;
    char* rhs_str = str2_v->str + str2_v->strlen - 1;
    while (lhs_str - str1_v->str > 0 && rhs_str - str2_v->str > 0) {
//        передвигаем указатель назад, пока не найдем букву
        while (!isalpha(*lhs_str)) {
            --lhs_str;
        }
        while (!isalpha(*rhs_str)) {
            --rhs_str;
        }
//        сравниваем
        if (*lhs_str > *rhs_str) {
            return 1;
        } else if (*lhs_str < *rhs_str) {
            return -1;
        }
//        сдвигаем назад
        --lhs_str;
        --rhs_str;
    }
    return 0;
}

/*
 * quicksort по схеме Хоара
 * */
int partition(struct strview* arrOfStrings, int leftIndex, int rightIndex,
        int (*comp)(const void* str1, const void* str2)) {
    int l_index = leftIndex;
    int r_index = rightIndex;
    struct strview* sample = &arrOfStrings[(l_index + r_index) / 2];

    while (l_index < r_index) {
        while (comp(&arrOfStrings[l_index], sample) < 0) {
            ++l_index;
        }
        while (comp(&arrOfStrings[r_index], sample) > 0) {
            --r_index;
        }
        if (l_index >= r_index) {
            break;
        }

        struct strview tmp = arrOfStrings[l_index];
        arrOfStrings[l_index] = arrOfStrings[r_index];
        arrOfStrings[r_index] = tmp;

        l_index++;
        r_index--;
    }
    return r_index;
}

void quicksort(struct strview* array, int l_index, int r_index,
               int (*comp)(const void* str1, const void* str2)) {
    if (l_index < r_index) {
        int sample_index = partition(array, l_index, r_index, comp);
        quicksort(array, l_index, sample_index, comp);
        quicksort(array, sample_index + 1, r_index, comp);
    }
}

void sort(struct strview* arrOfStrings, int nStrings,
        int (*comp)(const void* str1, const void* str2)) {
    quicksort(arrOfStrings, 0, nStrings - 1, comp);
}

void sort_forward(struct strview* index_buffer, size_t buffer_size) {
//    sort(index_buffer, buffer_size, forward_strcmp);
    qsort(index_buffer, buffer_size, sizeof(struct strview), forward_strcmp);
}

void sort_backward(struct strview* index_buffer, size_t buffer_size) {
//    sort(index_buffer, buffer_size, reversed_strcmp);
    qsort(index_buffer, buffer_size, sizeof(struct strview), reversed_strcmp);
}


//
// Created by kalibri on 09.09.2020.
//

#include "stringsort.h"
#include <string.h>


void sort(char** arrOfStrings, int nStrings) {
    int l_index = 0;
    int r_index = nStrings - 1;
    char* sample = arrOfStrings[(l_index + r_index) / 2];

    while (l_index < r_index) {
        while (strcmp(arrOfStrings[l_index], sample) < 0) {
            ++l_index;
        }
        while (strcmp(arrOfStrings[r_index], sample) > 0) {
            --r_index;
        }

        char* tmp = arrOfStrings[l_index];
        arrOfStrings[l_index] = arrOfStrings[r_index];
        arrOfStrings[r_index] = tmp;

        l_index++;
        r_index--;
    }
}

//
// Created by kalibri on 14.09.2020.
//

#include "tests.h"
#include "stringsort.h"
#include <assert.h>

char* empty = "../test_files/empty.txt";
char* not_only_letters = "../test_files/not_only_letters.txt";
char* one_string = "../test_files/one_string.txt";
char* same_strings = "../test_files/same_strings.txt";


void test_getFileSize() {
    assert(getFileSize(empty) == 0);
    assert(getFileSize(not_only_letters) == 41);
    assert(getFileSize(one_string) == 7);
    assert(getFileSize(same_strings) == 14);

}

void test_evaluateBuffer() {
    assert(evaluateBuffer(empty, 0, '\n', '\n') == 0);
    assert(evaluateBuffer(not_only_letters, 41, '\n', '\n') == 3);
    assert(evaluateBuffer(one_string, 7, '\n', '\n') == 1);
    assert(evaluateBuffer(same_strings, 14, '\n', '\n') == 2);
}

void test_forward_strcmp() {
    struct strview lhs;
    struct strview rhs;

    lhs.str = "abc";
    lhs.strlen = 3;

    rhs.str = "bbc";
    rhs.strlen = 3;

    assert(forward_strcmp(&lhs, &rhs) == -1);

    lhs.str = "ab";
    lhs.strlen = 2;

    rhs.str = "bbc";
    rhs.strlen = 3;

    assert(forward_strcmp(&lhs, &rhs) == -1);

    lhs.str = "a";
    lhs.strlen = 1;

    rhs.str = "a";
    rhs.strlen = 1;

    assert(forward_strcmp(&lhs, &rhs) == 0);
}

void test_reversed_strcmp() {
    struct strview lhs;
    struct strview rhs;

    lhs.str = "abc";
    lhs.strlen = 3;

    rhs.str = "bbc";
    rhs.strlen = 3;

    assert(reversed_strcmp(&lhs, &rhs) == -1);

    lhs.str = "ab";
    lhs.strlen = 2;

    rhs.str = "bbc";
    rhs.strlen = 3;

    assert(reversed_strcmp(&lhs, &rhs) == -1);

    lhs.str = "a";
    lhs.strlen = 1;

    rhs.str = "a";
    rhs.strlen = 1;

    assert(reversed_strcmp(&lhs, &rhs) == 0);
}

void run_all_tests() {
    test_getFileSize();
    test_evaluateBuffer();
    test_forward_strcmp();
    test_reversed_strcmp();
}

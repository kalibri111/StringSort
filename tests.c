//
// Created by kalibri on 14.09.2020.
//

#include "tests.h"
#include "stringsort.h"
#include <assert.h>

char* empty = "/home/kalibri/MIPT/1_sem/Dedinsky/StringSort/test_files/empty.txt";
char* not_only_letters = "/home/kalibri/MIPT/1_sem/Dedinsky/StringSort/test_files/not_only_letters.txt";
char* one_string = "/home/kalibri/MIPT/1_sem/Dedinsky/StringSort/test_files/one_string.txt";
char* same_strings = "/home/kalibri/MIPT/1_sem/Dedinsky/StringSort/test_files/same_strings.txt";


void test_getFileSize() {
    assert(getFileSize(empty) == 0);
    assert(getFileSize(not_only_letters) == 41);
    assert(getFileSize(one_string) == 7);
    assert(getFileSize(same_strings) == 14);

}

void test_fileRowsCount() {
    assert(fileRowsCount(empty) == 0);
    assert(fileRowsCount(not_only_letters) == 3);
    assert(fileRowsCount(one_string) == 1);
    assert(fileRowsCount(same_strings) == 2);
}

void test_makeIndex() {
    size_t            empty_size = fileRowsCount(empty);
    size_t not_only_letters_size = fileRowsCount(not_only_letters);
    size_t       one_string_size = fileRowsCount(one_string);
    size_t     same_strings_size = fileRowsCount(same_strings);

    size_t            empty_buf_size = getFileSize(empty);
    size_t not_only_letters_buf_size = getFileSize(not_only_letters);
    size_t       one_string_buf_size = getFileSize(one_string);
    size_t     same_strings_buf_size = getFileSize(same_strings);

    struct strview            empty_index[empty_size];
    struct strview not_only_letters_index[not_only_letters_size];
    struct strview       one_string_index[one_string_size];
    struct strview     same_strings_index[same_strings_size];

    char            empty_buffer[empty_buf_size];
    char not_only_letters_buffer[not_only_letters_buf_size];
    char       one_string_buffer[one_string_buf_size];
    char     same_strings_buffer[same_strings_buf_size];

    fileToBuff(empty, empty_buffer, empty_buf_size);
    fileToBuff(not_only_letters, not_only_letters_buffer, not_only_letters_buf_size);
    fileToBuff(one_string, one_string_buffer, one_string_buf_size);
    fileToBuff(same_strings, same_strings_buffer, same_strings_buf_size);

    makeIndex(empty_index, empty_buffer, empty_size);
    makeIndex(not_only_letters_index, not_only_letters_buffer, not_only_letters_size);
    makeIndex(one_string_index, one_string_buffer, one_string_size);
    makeIndex(same_strings_index, same_strings_buffer, same_strings_size);

    assert(sizeof(empty_index)/sizeof(empty_index[0]) == 0);
    assert(sizeof(not_only_letters_index)/sizeof(not_only_letters_index[0]) == 3);
    assert(sizeof(one_string_index)/sizeof(one_string_index[0]) == 1);
    assert(sizeof(same_strings_index)/sizeof(same_strings_index[0]) == 2);
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
    test_fileRowsCount();
    test_makeIndex();
    test_forward_strcmp();
    test_reversed_strcmp();
}

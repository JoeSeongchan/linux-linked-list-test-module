//
// Created by seongchan-joe on 21. 11. 8..
//

#ifndef LINKED_LIST_TEST_MODULE_UTILITIES_H
#define LINKED_LIST_TEST_MODULE_UTILITIES_H

#define log(...) logFn(__func__,##__VA_ARGS__)

#include "data_structure.h"

void logFn(const char *caller_name, const char *fmt, ...);

#endif //LINKED_LIST_TEST_MODULE_UTILITIES_H

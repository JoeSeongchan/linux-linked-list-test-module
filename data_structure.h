//
// Created by seongchan-joe on 21. 10. 28..
//

#ifndef LINKED_LIST_TEST_MODULE_DATA_STRUCTURE_H
#define LINKED_LIST_TEST_MODULE_DATA_STRUCTURE_H

#include "macro.h"
typedef struct _data_structure {
    list_head head;
    unsigned long long data;
} data_structure;

data_structure *init_data_structure(unsigned long long data);
void *free_data_structure(data_structure *target);
#endif //LINKED_LIST_TEST_MODULE_DATA_STRUCTURE_H

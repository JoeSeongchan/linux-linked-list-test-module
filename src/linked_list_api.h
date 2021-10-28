//
// Created by seongchan-joe on 21. 10. 28..
//

#ifndef LINKED_LIST_TEST_MODULE_LINKED_LIST_API_H
#define LINKED_LIST_TEST_MODULE_LINKED_LIST_API_H

#include "data_structure.h"

data_structure *list_search(struct list_head *head, unsigned long long data);

void list_delete(struct list_head *head, unsigned long long data);

void list_print_all_items(struct list_head *head);

#endif //LINKED_LIST_TEST_MODULE_LINKED_LIST_API_H

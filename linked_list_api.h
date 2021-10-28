//
// Created by seongchan-joe on 21. 10. 28..
//

#ifndef LINKED_LIST_TEST_MODULE_LINKED_LIST_API_H
#define LINKED_LIST_TEST_MODULE_LINKED_LIST_API_H

#include "macro.h"
#include "data_structure.h"

void list_add(list_head *newNode, list_head *head);

void list_add_tail(list_head *newNode, list_head *head);

void list_del(list_head *entry);

data_structure *list_search(list_head *head, unsigned long long data);

data_structure *list_delete(list_head *head, unsigned long long data);

void list_print_all_items(list_head *head);

#endif //LINKED_LIST_TEST_MODULE_LINKED_LIST_API_H

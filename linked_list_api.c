//
// Created by seongchan-joe on 21. 10. 28..
//
#include <stdio.h>
#include "linked_list_api.h"
#include "stdlib.h"

void list_add(list_head *newNode, list_head *head) {
    list_head *next = head->next;
    next->prev = newNode;
    newNode->next = next;
    head->next = newNode;
    newNode->prev = head;
}

void list_add_tail(list_head *newNode, list_head *head) {
    list_head *prev = head->prev;
    head->prev = newNode;
    newNode->next = head;
    prev->next = newNode;
    newNode->prev = prev;
}

void list_del(list_head *entry) {
    list_head *next = entry->next;
    list_head *prev = entry->prev;
    entry->prev = 0;
    entry->next = 0;
    prev->next = next;
    next->prev = prev;
}

data_structure *list_search(list_head *head, unsigned long long data) {
    data_structure *pos = NULL;
    data_structure *pos_next = NULL;
    list_for_each_entry_safe(pos, pos_next, head, head) {
        if (pos->data == data) {
            return pos;
        }
    }
    return NULL;
}

data_structure *list_delete(list_head *head, unsigned long long data) {
    data_structure *pos = NULL;
    data_structure *pos_next = NULL;
    list_for_each_entry_safe(pos, pos_next, head, head) {
        if (pos->data == data) {
            list_del(&pos->head);
            return pos;
        }
    }
    return NULL;
}

void list_print_all_items(list_head *head) {
    data_structure *pos = NULL;
    data_structure *pos_next = NULL;
    unsigned long long i = 0;
    list_for_each_entry_safe(pos, pos_next, head, head) {
        // printf("#%d node data : %d\n", i, pos->data);
        i += 1;
    }
}








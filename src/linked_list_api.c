//
// Created by seongchan-joe on 21. 10. 28..
//
#include "linked_list_api.h"

data_structure *list_search(struct list_head *head, unsigned long long data) {
    data_structure *pos = NULL;
    data_structure *pos_next = NULL;
    list_for_each_entry_safe(pos, pos_next, head, head) {
        if (pos->data == data) {
            return pos;
        }
    }
    return NULL;
}

void list_delete(struct list_head *head, unsigned long long data) {
    data_structure *pos = NULL;
    data_structure *pos_next = NULL;
    list_for_each_entry_safe(pos, pos_next, head, head) {
        if (pos->data == data) {
            list_del(&pos->head);
            kfree(pos);
            return;
        }
    }
    return;
}

void list_print_all_items(struct list_head *head) {
    data_structure *pos = NULL;
    data_structure *pos_next = NULL;
    unsigned long long i = 0;
    list_for_each_entry_safe(pos, pos_next, head, head) {
        printk("#%llu node data : %llu\n", i, pos->data);
        i += 1;
    }
}








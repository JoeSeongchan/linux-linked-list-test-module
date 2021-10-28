//
// Created by seongchan-joe on 21. 10. 28..
//
#include "data_structure.h"

struct list_head *init_sentinel_node(void) {
    struct list_head *sentinel_node = (struct list_head *) kmalloc(sizeof(struct list_head), GFP_KERNEL);
    INIT_LIST_HEAD(sentinel_node);
    return sentinel_node;
}

data_structure *init_data_structure(unsigned long long data) {
    data_structure *new_node = (data_structure *) kmalloc(sizeof(data_structure), GFP_KERNEL);
    new_node->data = data;
//    new_node->head.next = &new_node->head;
//    new_node->head.prev = &new_node->head;
    return new_node;
}

void free_data_structure(data_structure *target) {
    kfree(target);
}

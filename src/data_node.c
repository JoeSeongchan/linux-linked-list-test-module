//
// Created by seongchan-joe on 21. 10. 28..
//
#include "data_node.h"

struct rb_node *init_root_rb_node(void) {
    struct rb_node *root_node = (struct rb_node *) kmalloc(sizeof(struct rb_node), GFP_KERNEL);
    *root_node = RB_ROOT;
    return root_node;
}

data_node *init_new_data_node(unsigned long long data) {
    data_node *new_data_node = (data_node *) kmalloc(sizeof(data_node), GFP_KERNEL);
    new_data_node->data = data;
//    new_node->head.next = &new_node->head;
//    new_node->head.prev = &new_node->head;
    return new_data_node;
}

void free_data_node(data_structure *target) {
    kfree(target);
}

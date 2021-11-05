//
// Created by seongchan-joe on 21. 10. 28..
//

#ifndef DATA_NODE_TEST_MODULE_DATA_NODE_H
#define DATA_NODE_TEST_MODULE_DATA_NODE_H

#include <linux/kernel.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

typedef struct _data_node {
    struct rb_node node;
    unsigned long long data;
} data_node;

struct rb_node *init_root_rb_node(void);

data_node *init_new_data_node(unsigned long long data);

void free_data_node(data_node *target);

#endif //DATA_NODE_TEST_MODULE_DATA_NODE_H

//
// Created by seongchan-joe on 21. 10. 28..
//
#include "rb_tree_api.h"

data_node *node_search(struct rb_root *root, unsigned long long data) {
    struct rb_node *cur_rb_node = root->rb_node;
    int result = 0;
    while(cur_rb_node){
        // find current data node.
        data_node *cur_data_node = container_of(cur_rb_node,data_node,node);
        // compare data and find next data node.
        result = data - cur_data_node->data;
        if(result < 0){
            cur_data_node = cur_data_node->rb_left;
        }else if(result > 0){
            cur_data_node = cur_data_node->rb_right;
        }else{
            // when we find target.
            return cur_data_node;
        }
    }
    // when we can't find target.
    return NULL;
}

int node_insert(struct rb_root *root, data_node *data){
    struct rb_node **new = &(root->rb_node), *parent = NULL;
    int result = 0;
    // figure out where to put new node.
    while(*new){
        data_node *this = container_of(*new, data_node, node);
        result = data->data - this->data;
        if(result < 0){
            new = &((*new)->rb_left);
        }else if(result > 0){
            new = &((*new)->rb_right);
        }else{
            // when data is already existed in tree.
            return FALSE;
        }
        // add new node and rebalance tree.
        rb_link_node(&data->node,parent,new);
        rb_insert_color(&data->node,root);

        return TRUE;
    }
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








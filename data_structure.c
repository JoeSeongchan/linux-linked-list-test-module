//
// Created by seongchan-joe on 21. 10. 28..
//

#include <stdlib.h>
#include "data_structure.h"

data_structure *init_data_structure(unsigned long long data) {
    data_structure *new_node = (data_structure *) malloc(sizeof(data_structure));
    new_node->data = data;
    new_node->head.next = &new_node->head;
    new_node->head.prev = &new_node->head;
    return new_node;
}

void *free_data_structure(data_structure *target) {
    free(target);
}

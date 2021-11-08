//
// Created by seongchan-joe on 21. 10. 29..
//

#include "rb_tree_api.h"
#include "time_calculating.h"

MODULE_LICENSE ("GPL v2");

// function to create an integer array. [start_val, start_val+1, ... , end_val]
int *make_ordered_data_list(int start_val, int end_val) {
    int arr_length = end_val - start_val + 1;
    int *data_list = kmalloc(sizeof(int) * arr_length, GFP_KERNEL);
    for (int i = 0, val = start_val; i < arr_length; i++, val++) {
        data_list[i] = val;
    }
    return data_list;
}

// function to mix the sequence of the array.
void shuffle(int *arr, int arr_length) {
    int temp;
    int random_number;
    unsigned int val = 0;
    for (int i = 0; i < arr_length - 1; i++) {
        get_random_bytes(&val, sizeof(unsigned int));
        random_number = (unsigned int) (val % (arr_length - i) + i); // Pick a number randomly from i ~ arr_length-1.
        // swap.
        temp = arr[i];
        arr[i] = arr[random_number];
        arr[random_number] = temp;
    }
}

// function to measure time to copy "item_num" items from int array into data_node array.
unsigned long long measure_insert_time(struct list_head *sentinel, int *arr, int item_num) {
    struct timespec64 start_time, end_time;
    data_node *new_node = NULL;
    ktime_get_raw_ts64(&start_time);
    for (unsigned long long i = 0; i < item_num; i++) {
        new_node = init_data_node(arr[i]);
        list_add(&new_node->head, sentinel);
    }
    ktime_get_raw_ts64(&end_time);
    struct timespec64 spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// function to measure time to find item in the linked list.
// target item = One of the items in the target_list.
unsigned long long measure_search_time(struct list_head *sentinel, int *target_list, int target_num) {
    struct timespec64 start_time, end_time;
    ktime_get_raw_ts64(&start_time);
    data_node *search_result;
    int counter = 0;
    for (int i = 0; i < target_num; i++) {
        search_result = list_search(sentinel, target_list[i]);
        if (search_result != NULL) {
            counter++;
        }
    }
    ktime_get_raw_ts64(&end_time);
    struct timespec64 spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    if (counter != target_num) {
        return ULLONG_MAX;
    }
    return time_diff;
}

// function to measure time to remove item from the linked list.
// target item = One of the items in the target_list.
unsigned long long measure_delete_time(struct list_head *sentinel, int *target_list, int target_num) {
    struct timespec64 start_time, end_time;
    ktime_get_raw_ts64(&start_time);
    int result;
    int counter = 0;
    for (int i = 0; i < target_num; i++) {
        result = list_delete(sentinel, target_list[i]);
        if (result) {
            counter++;
        }
    }
    ktime_get_raw_ts64(&end_time);
    struct timespec64 spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    if (counter != target_num) {
        return ULLONG_MAX;
    }
    return time_diff;
}

// function to print the time it took to add n nodes.
void insert_n_items(int item_num) {
    struct list_head *sentinel = init_sentinel();
    int *data_list = make_ordered_data_list(0, item_num - 1);
    unsigned long long elapsed_time = measure_insert_time(sentinel, data_list, item_num);
    kfree(data_list);
    list_delete_all(sentinel);
    log("---example of insertion--\n"
        "number of items : %d\n"
        "elpased time : %llu sec, %llu nsec", item_num, elapsed_time / BILLION, elapsed_time % BILLION);
}

// function to print the time it took to search n nodes.
void search_n_items(int item_num) {
    struct list_head *sentinel = init_sentinel();
    int *data_list = make_ordered_data_list(0, item_num - 1);
    measure_insert_time(sentinel, data_list, item_num);
    shuffle(data_list, item_num);
    unsigned long long elapsed_time = measure_search_time(sentinel, data_list, item_num);
    kfree(data_list);
    list_delete_all(sentinel);
    if (elapsed_time == ULLONG_MAX) {
        log("---example of searching--\n"
            "number of items : %d\n"
            "there is an item that program couldn't find.");
    } else {
        log("---example of searching--\n"
            "number of items : %d\n"
            "elpased time : %llu sec, %llu nsec", item_num, elapsed_time / BILLION, elapsed_time % BILLION);
    }
}

// function to print the time it took to delete n nodes.
void delete_n_items(unsigned long long item_num) {
    struct list_head *sentinel = init_sentinel();
    int *data_list = make_ordered_data_list(0, item_num - 1);
    measure_insert_time(sentinel, data_list, item_num);
    shuffle(data_list, item_num);
    unsigned long long elapsed_time = measure_delete_time(sentinel, data_list, item_num);
    kfree(data_list);
    list_delete_all(sentinel);
    if (elapsed_time == ULLONG_MAX) {
        log("---example of deletion--\n"
            "number of items : %d\n"
            "there is an item that program couldn't find.");
    } else {
        log("---example of deletion--\n"
            "number of items : %d\n"
            "elpased time : %llu sec, %llu nsec", item_num, elapsed_time / BILLION, elapsed_time % BILLION);
    }
}

// function to run assignment 7.
void run_assign_7(void) {
    // Example of insertion
    insert_n_items(1000);
    insert_n_items(10000);
    insert_n_items(100000);

    // Example of Searching
    search_n_items(1000);
    search_n_items(10000);
    search_n_items(100000);

    // Example of Deletion
    delete_n_items(1000);
    delete_n_items(10000);
    delete_n_items(100000);

    log("End. Thank you.");
}

int __init

test_linked_list_module_init(void) {
    printk("\n");
    run_assign_7();
    return 0;
}

void __exit

test_linked_list_module_cleanup(void) {
    log("Module that tests the linked list in linux kernel.\n"
        "LINUX SYSTEM AND ITS APPLICATIONS\n"
        "Subclass : 02\n"
        "ID : 20160570\n"
        "Name : Joe Seong-chan\n");
    return;
}

module_init(test_linked_list_module_init);
module_exit(test_linked_list_module_cleanup);


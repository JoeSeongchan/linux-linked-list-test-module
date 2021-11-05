//
// Created by seongchan-joe on 21. 10. 29..
//

#include "rb_tree_api.h"
#include "time_calculating.h"
#include <linux/init.h>
#include <linux/random.h>
#include <linux/module.h>

MODULE_LICENSE ("GPL v2");

// Create an integer array. [start_val, start_val+1, ... , end_val]
unsigned long long *make_ordered_data_list(unsigned long long start_val, unsigned long long end_val) {
    unsigned long long arr_length = end_val - start_val + 1;
    unsigned long long *data_list = kmalloc(sizeof(unsigned long long) * arr_length,GFP_KERNEL);
    for (unsigned long long i = 0, val = start_val; i < arr_length; i++, val++) {
        data_list[i] = val;
    }
    return data_list;
}

// Mix the sequence of the array.
void shuffle(unsigned long long *arr, unsigned long long arr_length) {
    unsigned long long temp;
    unsigned long long random_number;
    unsigned long long val=0;
    for (unsigned long long i = 0; i < arr_length - 1; i++) {
        get_random_bytes(&val, sizeof(unsigned long long));
        random_number = (unsigned long long) (val % (arr_length - i) + i); // Pick a number randomly from i ~ arr_length-1.
        // swap.
        temp = arr[i];
        arr[i] = arr[random_number];
        arr[random_number] = temp;
    }
}

// Copy "item_num" items from unsigned long long array into data_structure array.
unsigned long long get_insert_time(struct list_head *head, unsigned long long *arr, unsigned long long item_num) {
    struct timespec64 start_time, end_time;
    data_structure *new_node = NULL;
    ktime_get_raw_ts64(&start_time);
    for (unsigned long long i = 0; i < item_num; i++) {
        new_node = init_data_structure(arr[i]);
        list_add(&new_node->head, head);
    }
    ktime_get_raw_ts64(&end_time);
    struct timespec64 spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// Find item in the linked list.
// target item = One of the items in the target_list.
unsigned long long get_search_time(struct list_head *head, unsigned long long *target_list, unsigned long long target_num) {
    struct timespec64 start_time, end_time;
    ktime_get_raw_ts64(&start_time);
    data_structure *search_result;
    unsigned long long success_count = 0;
    for (unsigned long long i = 0; i < target_num; i++) {
        search_result = list_search(head, target_list[i]);
        if (search_result != NULL) {
            // printk("#%llu element is found. val : %llu, node val : %llu\n", i, target_list[i], search_result->data);
            success_count++;
        }
    }
    ktime_get_raw_ts64(&end_time);
    struct timespec64 spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// Remove item from the linked list.
// target item = One of the items in the target_list.
unsigned long long get_delete_time(struct list_head *head, unsigned long long *target_list, unsigned long long target_num) {
    struct timespec64 start_time, end_time;
    ktime_get_raw_ts64(&start_time);
    for (unsigned long long i = 0; i < target_num; i++) {
        list_delete(head, target_list[i]);
    }
    ktime_get_raw_ts64(&end_time);
    struct timespec64 spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// Remove all item from the linked list.
void remove_all_item(struct list_head *head) {
    data_structure *current_node = NULL, *next_node = NULL;
    list_for_each_entry_safe(current_node, next_node, head, head) {
        list_del(&current_node->head);
        kfree(current_node);
    }
}

// list_length 개의 노드를 추가. 시간 재고, 이를 콘솔에 출력.
void insert_n_items(unsigned long long item_num) {
    struct list_head *head=init_sentinel_node();
    unsigned long long *data_list = make_ordered_data_list(0, item_num - 1);
    unsigned long long elapsed_time = get_insert_time(head, data_list, item_num);
    // list_print_all_items(head);
    kfree(data_list);
    remove_all_item(head);
    kfree(head);
    printk("---Example of Insertion---\n");
    printk("Number of items : %llu\n", item_num);
    printk("Elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    printk("\n");
}

// list_length 개의 노드 찾기. 시간 재고, 이를 콘솔에 출력.
void search_n_items(unsigned long long item_num) {
    struct list_head *head=init_sentinel_node();
    unsigned long long *data_list = make_ordered_data_list(0, item_num - 1);
    get_insert_time(head, data_list, item_num);
    shuffle(data_list, item_num);
    unsigned long long elapsed_time = get_search_time(head, data_list, item_num);
    kfree(data_list);
    remove_all_item(head);
    kfree(head);
    printk("---Example of Searching---\n");
    printk("Number of items : %llu\n", item_num);
    printk("Elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    printk("\n");
}

// list_length 개의 노드 삭제하기. 시간 재고, 이를 콘솔에 출력.
void delete_n_items(unsigned long long item_num) {
    struct list_head *head=init_sentinel_node();
    unsigned long long *data_list = make_ordered_data_list(0, item_num - 1);
    get_insert_time(head, data_list, item_num);
    shuffle(data_list, item_num);
    unsigned long long elapsed_time = get_delete_time(head, data_list, item_num);
    kfree(data_list);
    remove_all_item(head);
    kfree(head);
    printk("---Example of Deletion---\n");
    printk("Number of items : %llu\n", item_num);
    printk("Elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    printk("\n");
}

// 데이터 노드 다루는 함수.
void run_assign_6(void) {
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

    printk("End. Thank you.\n");
}

void arr_print_all_items(unsigned long long *arr, unsigned long long arr_length) {
    for (unsigned long long i = 0; i < arr_length; i++) {
        printk("#%llu element val : %llu\n", i, arr[i]);
    }
}

int __init test_linked_list_module_init(void){
#ifdef FALSE
    printk("- test for \"make_ordered_data_list\" -\n");
    unsigned long long *int_arr = make_ordered_data_list(0, 9);
    arr_print_all_items(int_arr,10);
    printk("\n");

    printk("- test for \"shuffle\" -\n");
    shuffle(int_arr, 10);
    arr_print_all_items(int_arr,10);
    printk("\n");

    printk("- test for \"get_insert_time\" -\n");
    struct list_head *sample_node_list=init_sentinel_node();
    unsigned long long sample_data_arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned long long elapsed_time = get_insert_time(sample_node_list, sample_data_arr, 10);
    list_print_all_items(sample_node_list);
    printk("elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);

    printk("- test for \"get_search_time\" -\n");
    shuffle(sample_data_arr, 10);
    printk("- sample data arr- \n");
    arr_print_all_items(sample_data_arr, 10);
    elapsed_time = get_search_time(sample_node_list, sample_data_arr, 10);
    printk("elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);

    printk("- test for \"get_delete_time\" -\n");
    shuffle(sample_data_arr, 10);
    printk("- sample data arr- \n");
    arr_print_all_items(sample_data_arr, 10);
    elapsed_time = get_delete_time(sample_node_list, sample_data_arr, 10);
    printk("elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    list_print_all_items(sample_node_list);
    unsigned long long sample_data_arr_2[3] = {9, 99, 999};
    get_insert_time(sample_node_list, sample_data_arr_2, 3);
    list_print_all_items(sample_node_list);
    elapsed_time = get_delete_time(sample_node_list, sample_data_arr_2, 3);
    printk("elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    list_print_all_items(sample_node_list);

    printk("- test for \"remove_all_item\" -\n");
    kfree(int_arr);
    int_arr = make_ordered_data_list(0, 19);
    get_insert_time(sample_node_list, int_arr, 20);
    list_print_all_items(sample_node_list);
    remove_all_item(sample_node_list);
    list_print_all_items(sample_node_list);

    // printf("- test for \"insert_n_items\" -\n");
    insert_n_items(10000);

    // printf("- test for \"search_n_items\" -\n");
    search_n_items(100);

    // printf("- test for \"delete_n_items\" -\n");
    delete_n_items(100);
#endif
    printk("\n");
    run_assign_6();
#ifdef FALSE
    // Example of Deletion
    delete_n_items(1000);
    delete_n_items(10000);
    delete_n_items(100000);
#endif
    return 0;
}

void __exit test_linked_list_module_cleanup(void){
    printk("Module that tests the linked list in linux kernel.\n");
    printk("--------------------------------------------------\n");
    printk("LINUX SYSTEM AND ITS APPLICATIONS\n");
    printk("Subclass : 02\n");
    printk("ID : 20160570\n");
    printk("Name : Joe Seong-chan\n");
    return;
}

module_init(test_linked_list_module_init);
module_exit(test_linked_list_module_cleanup);


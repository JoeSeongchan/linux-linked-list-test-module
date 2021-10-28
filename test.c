//
// Created by seongchan-joe on 21. 10. 28..
//
#define _POSIX_C_SOURCE 199309L


#include <stdlib.h>
#include <time.h>
#include "linked_list_api.h"
#include "time_calculating.h"
#include <stdio.h>

// Create an integer array. [start_val, start_val+1, ... , end_val]
unsigned long long *make_ordered_data_list(unsigned long long start_val, unsigned long long end_val) {
    unsigned long long arr_length = end_val - start_val + 1;
    unsigned long long *data_list = malloc(sizeof(unsigned long long) * arr_length);
    for (unsigned long long i = 0, val = start_val; i < arr_length; i++, val++) {
        data_list[i] = val;
    }
    return data_list;
}

// Mix the sequence of the array.
void shuffle(unsigned long long *arr, unsigned long long arr_length) {
    srand(time(NULL));  // create seed.
    unsigned long long temp;
    unsigned long long random_number;
    for (unsigned long long i = 0; i < arr_length - 1; i++) {
        random_number = (unsigned long long) (rand() % (arr_length - i) + i); // Pick a number randomly from i ~ arr_length-1.
        // swap.
        temp = arr[i];
        arr[i] = arr[random_number];
        arr[random_number] = temp;
    }
}

// Copy "item_num" items from unsigned long long array into data_structure array.
unsigned long long get_insert_time(list_head *head, unsigned long long *arr, unsigned long long item_num) {
    struct timespec start_time, end_time;
    data_structure *new_node = NULL;
    clock_gettime(CLOCK_MONOTONIC, &start_time); // 시간 재기 시작.
    for (unsigned long long i = 0; i < item_num; i++) {
        new_node = init_data_structure(arr[i]);
        list_add(&new_node->head, head);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);   // 시간 재기 끝.
    struct timespec spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// Find item in the linked list.
// target item = One of the items in the target_list.
unsigned long long get_search_time(list_head *head, unsigned long long *target_list, unsigned long long target_num) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    data_structure *search_result;
    unsigned long long success_count = 0;
    for (unsigned long long i = 0; i < target_num; i++) {
        search_result = list_search(head, target_list[i]);
        if (search_result != NULL) {
            // printf("#%d element is found. val : %d, node val : %d\n", i, target_list[i], search_result->data);
            success_count++;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    struct timespec spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// Remove item from the linked list.
// target item = One of the items in the target_list.
unsigned long long get_delete_time(list_head *head, unsigned long long *target_list, unsigned long long target_num) {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    data_structure *delete_target = NULL;
    for (unsigned long long i = 0; i < target_num; i++) {
        delete_target = list_delete(head, target_list[i]);
        if (delete_target != NULL) {
            // printf("#%d element will be deleted. val : %d, node val : %d\n", i, target_list[i], delete_target->data);
            free_data_structure(delete_target);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    struct timespec spclock[2] = {start_time, end_time};
    unsigned long long time_diff = calclock3(spclock);
    return time_diff;
}

// Remove all item from the linked list.
void remove_all_item(list_head *head, unsigned long long node_num) {
    data_structure *current_node = NULL, *next_node = NULL;
    list_for_each_entry_safe(current_node, next_node, head, head) {
        list_del(&current_node->head);
        free(current_node);
    }
}

// list_length 개의 노드를 추가. 시간 재고, 이를 콘솔에 출력.
void insert_n_items(unsigned long long item_num) {
    data_structure *node_list = init_data_structure(-1);
    unsigned long long *data_list = make_ordered_data_list(0, item_num - 1);
    unsigned long long elapsed_time = get_insert_time(&node_list->head, data_list, item_num);
    list_print_all_items(&node_list->head);
    free(data_list);
    remove_all_item(&node_list->head, item_num);
    free(node_list);
    printf("---Example of Insertion---\n");
    printf("Number of items : %d\n", item_num);
    printf("Elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    printf("\n");
}

// list_length 개의 노드 찾기. 시간 재고, 이를 콘솔에 출력.
void search_n_items(unsigned long long item_num) {
    data_structure *node_list = init_data_structure(-1);
    unsigned long long *data_list = make_ordered_data_list(0, item_num - 1);
    get_insert_time(&node_list->head, data_list, item_num);
    shuffle(data_list, item_num);
    unsigned long long elapsed_time = get_search_time(&node_list->head, data_list, item_num);
    free(data_list);
    remove_all_item(&node_list->head, item_num);
    free(node_list);
    printf("---Example of Searching---\n");
    printf("Number of items : %d\n", item_num);
    printf("Elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    printf("\n");
}

// list_length 개의 노드 삭제하기. 시간 재고, 이를 콘솔에 출력.
void delete_n_items(unsigned long long item_num) {
    data_structure *node_list = init_data_structure(-1);
    unsigned long long *data_list = make_ordered_data_list(0, item_num - 1);
    get_insert_time(&node_list->head, data_list, item_num);
    shuffle(data_list, item_num);
    unsigned long long elapsed_time = get_delete_time(&node_list->head, data_list, item_num);
    free(data_list);
    remove_all_item(&node_list->head, item_num);
    free(node_list);
    printf("---Example of Deletion---\n");
    printf("Number of items : %d\n", item_num);
    printf("Elapsed time : %llu sec, %llu nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    printf("\n");
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

    printf("End. Thank you.\n");
}

void arr_print_all_items(unsigned long long *arr, unsigned long long arr_length) {
    for (unsigned long long i = 0; i < arr_length; i++) {
        printf("#%d element val : %d\n", i, arr[i]);
    }
}

int main(int argc, char *argv[]) {
#ifdef FALSE
    // printf("- test for \"make_ordered_data_list\" -\n");
    int *int_arr = make_ordered_data_list(0, 10);

    for (unsigned int i = 0; i < 10; i++) {
        // printf("#%d element : %d\n", i, int_arr[i]);
    }
    // printf("\n");

    // printf("- test for \"shuffle\" -\n");
    shuffle(int_arr, 10);
    for (unsigned int i = 0; i < 10; i++) {
        // printf("#%d element : %d\n", i, int_arr[i]);
    }
    // printf("\n");

    // printf("- test for \"get_insert_time\" -\n");
    data_structure *sample_node_list = init_data_structure(-1);
    int sample_data_arr[3] = {0, 1, 2};
    unsigned long long elapsed_time = get_insert_time(&sample_node_list->head, sample_data_arr, 3);
    list_print_all_items(&sample_node_list->head);
    // printf("elapsed time : %d sec, %d nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);

    // printf("- test for \"get_search_time\" -\n");
    shuffle(sample_data_arr, 3);
    // printf("- sample data arr- \n");
    arr_print_all_items(sample_data_arr, 3);
    elapsed_time = get_search_time(&sample_node_list->head, sample_data_arr, 3);
    // printf("elapsed time : %d sec, %d nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);

    // printf("- test for \"get_delete_time\" -\n");
    shuffle(sample_data_arr, 3);
    // printf("- sample data arr- \n");
    arr_print_all_items(sample_data_arr, 3);
    elapsed_time = get_delete_time(&sample_node_list->head, sample_data_arr, 3);
    // printf("elapsed time : %d sec, %d nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);
    int sample_data_arr_2[2] = {9, 99};
    get_insert_time(&sample_node_list->head, sample_data_arr_2, 2);
    list_print_all_items(&sample_node_list->head);
    elapsed_time = get_delete_time(&sample_node_list->head, sample_data_arr_2, 2);
    // printf("elapsed time : %d sec, %d nsec\n", elapsed_time / BILLION, elapsed_time % BILLION);

    // printf("- test for \"remove_all_item\" -\n");
    free(int_arr);
    int_arr = make_ordered_data_list(0, 19);
    get_insert_time(&sample_node_list->head, int_arr, 20);
    list_print_all_items(&sample_node_list->head);
    remove_all_item(&sample_node_list->head, 20);
    list_print_all_items(&sample_node_list->head);

    // printf("- test for \"insert_n_items\" -\n");
    insert_n_items(10000);

    // printf("- test for \"search_n_items\" -\n");
    search_n_items(100);

    // printf("- test for \"delete_n_items\" -\n");
    delete_n_items(100);
#endif
    run_assign_6();
    return 0;
}


//
// Created by seongchan-joe on 21. 10. 28..
//

#ifndef LINKED_LIST_TEST_MODULE_MACRO_H
#define LINKED_LIST_TEST_MODULE_MACRO_H

// header
typedef struct _list_head {
    struct _list_head *prev;
    struct _list_head *next;
} list_head;

// find structure ptr
#define list_entry(ptr, type, member) \
    container_of(ptr,type,member)

// find member offset
#define offsetof(TYPE, MEMBER) \
    ((size_t) &((TYPE*)0)->MEMBER)

// find structure ptr
#define container_of(ptr, type, member) \
({const __typeof__( ((type *)0)->member ) *__mptr=(ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define list_for_each(pos, head) \
    for(pos=(head)->next; \
    pos!=(head); \
    pos=pos->next)

#define list_for_each_entry(pos, head, member) \
    for(pos=list_entry((head)->next,__typeof__(*pos),member); \
    &(pos->member)!=(head); \
    pos=list_entry(pos->member.next,__typeof__(*pos),member))

#define list_first_entry(head, type, member) \
    container_of(head->next,type,member)

#define list_next_entry(pos, member) \
    container_of(pos->member.next, __typeof__(*pos), member)

#define list_for_each_entry_safe(pos, n, head, member) \
    for(pos=list_first_entry(head,__typeof__(*pos), member), \
    n=list_next_entry(pos,member); \
    &pos->member!=(head); \
    pos=n, n=list_next_entry(n, member))


#endif //LINKED_LIST_TEST_MODULE_MACRO_H

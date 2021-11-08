//
// Created by seongchan-joe on 21. 11. 8..
//


#include "utilities.h"

// function to log.
void logFn(const char *caller_name, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printk("-----------------------\n");
    printk("FN : %s\n", caller_name);
    printk("MSG : ");
    vprintk(fmt, args);
    va_end(args);
}
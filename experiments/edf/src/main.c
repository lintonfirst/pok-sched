#include <libc/stdio.h>
#include <libc/string.h>
#include <core/thread.h>
#include <core/partition.h>
#include <types.h>

static void task();

int main() {
    uint32_t tid;
    pok_thread_attr_t tattr;
    memset(&tattr, 0, sizeof(pok_thread_attr_t));

    tattr.period = 100000000;
    tattr.time_capacity = 10;
    tattr.deadline = 100000000;
    tattr.entry = task;
    pok_thread_create(&tid, &tattr);

    tattr.period = 80000000;
    tattr.time_capacity = 20;
    tattr.deadline = 60000000;
    tattr.entry = task;
    pok_thread_create(&tid, &tattr);

    tattr.period = 100000000;
    tattr.time_capacity = 30;
    tattr.deadline = 50000000;
    tattr.entry = task;
    pok_thread_create(&tid, &tattr);

    pok_partition_set_mode(POK_PARTITION_MODE_NORMAL);
    pok_thread_wait_infinite();
    return 0;
}

static void task() {
    for (;;) {
        // printf("ok\n");
        // break;
    }
}

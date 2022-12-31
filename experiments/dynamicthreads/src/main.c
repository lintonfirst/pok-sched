#include <libc/stdio.h>
#include <libc/string.h>
#include <core/thread.h>
#include <core/partition.h>
#include <types.h>

static void task();
static void job();

int main() {
    uint32_t tid;
    pok_thread_attr_t tattr;
    memset(&tattr, 0, sizeof(pok_thread_attr_t));

    tattr.period = 100000000;
    tattr.time_capacity = 10;
    tattr.priority = 30;
    tattr.entry = task;
    pok_thread_create(&tid, &tattr);

    // tattr.period = 80000000;
    // tattr.time_capacity = 20;
    // tattr.priority = 50;
    // tattr.entry = task;
    // pok_thread_create(&tid, &tattr);

    // tattr.period = 100000000;
    // tattr.time_capacity = 30;
    // tattr.priority = 20;
    // tattr.entry = task;
    // pok_thread_create(&tid, &tattr);

    pok_partition_set_mode(POK_PARTITION_MODE_NORMAL);
    pok_thread_wait_infinite();
    return 0;
}

static void task() {
    for (int i=0;i<7;i++) {
        uint32_t tid;
        pok_thread_attr_t tattr;
        memset(&tattr, 0, sizeof(pok_thread_attr_t));
        tattr.period = 100000000;
        tattr.time_capacity = 10;
        tattr.priority = 30;
        tattr.entry = job;
        pok_ret_t ret=pok_thread_create(&tid, &tattr) ;
        if (ret == POK_ERRNO_OK) {
            printf("Thread %u created dynamically\n",tid);
        }
        else{
            printf("error %u\n",ret);
        }
    }
    // pok_thread_wait_infinite();
}

static void job() {
    printf("start job\n");
    for (;;) {
    }
}
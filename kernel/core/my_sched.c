#include <core/my_sched.h>
#include <core/time.h>
#include <core/sched.h>
#include <core/thread.h>
#include <core/partition.h>
#include <core/debug.h>

uint32_t my_sched_priority(const uint32_t index_low, const uint32_t index_high, const uint32_t prev_thread,
                               const uint32_t current_thread) {
    uint32_t highest_property_thread = IDLE_THREAD;
    for(uint32_t index=index_low;index!=index_high;index++){
        if(pok_threads[index].state == POK_STATE_RUNNABLE && pok_threads[index].priority>pok_threads[highest_property_thread].priority){
            highest_property_thread=index;
        }
    }

    return highest_property_thread;
}

uint32_t my_sched_edf(const uint32_t index_low, const uint32_t index_high, const uint32_t prev_thread,
                               const uint32_t current_thread) {
    uint32_t highest_property_thread = IDLE_THREAD;
    for(uint32_t index=index_low;index!=index_high;index++){
        if(pok_threads[index].state != POK_STATE_RUNNABLE){
            continue;
        }
        if(pok_threads[index].deadline_stamp==0){
            continue;
        }
        if(highest_property_thread == IDLE_THREAD){
            highest_property_thread=index;
            continue;
        }
        if(pok_threads[index].deadline_stamp<pok_threads[highest_property_thread].deadline_stamp){
            highest_property_thread=index;
        }
    }

    return highest_property_thread;
}

uint32_t my_sched_rr(const uint32_t index_low, const uint32_t index_high, const uint32_t prev_thread,
                               const uint32_t current_thread) {
    uint32_t selected = IDLE_THREAD;
    if (pok_threads[current_thread].state == POK_STATE_RUNNABLE
        && pok_threads[current_thread].remaining_time_capacity > 0 && pok_threads[current_thread].budget > 0) {
        pok_threads[current_thread].budget--;
        printf("%u\n",current_thread);
        return current_thread;
    }
    for(uint32_t index=index_low;index!=index_high;index++){
        if(pok_threads[index].state != POK_STATE_RUNNABLE && index!=current_thread){
            selected=index;
        }
    }
    if(selected!=IDLE_THREAD){
        pok_threads[selected].budget=4;
    }
    printf("%u\n",selected);
    return selected;
}


uint32_t my_sched_wrr(const uint32_t index_low, const uint32_t index_high, const uint32_t prev_thread,
                               const uint32_t current_thread) {
    uint32_t selected = IDLE_THREAD;
    if (pok_threads[current_thread].state == POK_STATE_RUNNABLE
        && pok_threads[current_thread].remaining_time_capacity > 0 && pok_threads[current_thread].budget > 0) {
        pok_threads[current_thread].budget--;
        return current_thread;
    }
    for(uint32_t index=index_low;index!=index_high;index++){
        if(pok_threads[index].state != POK_STATE_RUNNABLE && index!=current_thread){
            selected=index;
        }
    }
    if(selected!=IDLE_THREAD){
        pok_threads[selected].budget=4*pok_threads[selected].weight;
    }
    printf("%u\n",selected);
    return selected;
}

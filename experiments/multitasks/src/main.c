#include <libc/stdio.h>
#include <libc/string.h>
#include <core/thread.h>
#include <core/partition.h>
#include <types.h>

uint32_t frameCounter=0;
uint32_t processCounter=0;
uint32_t detectedNum=0;
uint32_t sendCounter=0;

static void fetch_video_frame();
static void unet_segmentation();
static void send_processed_frame();

int main() {
    uint32_t tid;
    pok_thread_attr_t tattr;
    memset(&tattr, 0, sizeof(pok_thread_attr_t));

    tattr.period = 100000000;
    tattr.time_capacity = 30;
    tattr.entry = fetch_video_frame;
    pok_thread_create(&tid, &tattr);

    tattr.period = 100000000;
    tattr.time_capacity = 20;
    tattr.entry = unet_segmentation;
    pok_thread_create(&tid, &tattr);

    tattr.period = 500000000;
    tattr.time_capacity = 15;
    tattr.entry = send_processed_frame;
    pok_thread_create(&tid, &tattr);

    pok_partition_set_mode(POK_PARTITION_MODE_NORMAL);
    pok_thread_wait_infinite();
    return 0;
}

static void fetch_video_frame() {
    while(1){
        for (int i=0;i<300000;i++) {
            ;
        }
        frameCounter+=1;
        printf("fetch: frameCounter %u,processCounter %u,sendCounter %u\n",frameCounter,processCounter,sendCounter);
    }
}

static void unet_segmentation() {
    while(1){
        if(frameCounter>processCounter){
            for (int i=0;i<200000;i++) {
                
            }
            processCounter+=1;
            if(processCounter%3==0||processCounter%7==0){
                detectedNum+=1;
            }
        }
        printf("unet: frameCounter %u,processCounter %u,sendCounter %u\n",frameCounter,processCounter,sendCounter);
    }
}

static void send_processed_frame() {
    while(1){
        if(detectedNum>10){
            for (int i=0;i<150000;i++) {
                ;
            }
            detectedNum-=10;
            sendCounter+=1;
        }
        printf("send: frameCounter %u,processCounter %u,sendCounter %u\n",frameCounter,processCounter,sendCounter);
    }
}

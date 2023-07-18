#pragma once

struct Thread {
    int platform;
    int id;
    char* myName;
    char* myHandle;
    int n_recips;
    char* recipNames;
    char* recipHandles;
    int* recipIds;
};

typedef Thread thread_t;
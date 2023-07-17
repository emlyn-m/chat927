struct Message {
    int platform;
    int threadid;
    int id;
    int senderId;
    int sentTime;
    int* seenByIds;
    int* seenTimes;
    char* content;
};

typedef Message message_t;
#include "message.h"
#include "thread.h"

class Instagram {
public:
    static constexpr char* ICON_URL = "./assets/instagram.png";

    void getApiToken(char* username, char* password, char* token);
    void getThread(char* token, int threadId, int nResults, int offset, message_t* results);
    void getAllThreads(char* token, thread_t* chats);
    
    int sendMessage(char* token, char* content);

};

typedef Instagram instagram_t;
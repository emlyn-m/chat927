#include "message.h"
#include "thread.h"

class Instagram {
public:
    static constexpr char* ICON_URL = "./assets/instagram.png";

    static constexpr char* SHARED_DATA_URL = "https://www.instagram.com/data/shared_data/";
    static constexpr char* LOGIN_URL = "https://www.instagram.com/api/v1/web/accounts/login/ajax/";

    static int encryptPassword(char*, int, int, int, char**);
    static int getApiToken(char*, char*, char**, char**);
    static int getThread(char* token, int threadId, int nResults, int offset, message_t* results);
    static int getAllThreads(char* token, thread_t* chats);
    
    static int sendMessage(char* token, int threadId, char* content);

};

typedef Instagram instagram_t;
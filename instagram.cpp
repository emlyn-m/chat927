#include <cstdlib>
#include <string.h>
#include <chrono>
#include <charconv>
#include <random>

#include <cpr/cpr.h>

#include "instagram.h"
#include "constants.h"




#include <iostream>

int Instagram::encryptPassword(char* password, int keyId, int version, int publicKey, char** enc_pwd) {
    // #PWD_INSTAGRAM_BROWSER:{version}:{unix_seconds}:{encrypted_password}

    int unix_time_s = std::chrono::duration_cast<std::chrono::seconds>(
                   std::chrono::system_clock::now().time_since_epoch()
                   ).count();
    char* unix_time_s_char = (char*) malloc(10 * sizeof(char));
    std::to_chars(unix_time_s_char, unix_time_s_char+10, unix_time_s);

    if (version == 0) {
        int pwdLen = 0;
        while (password[pwdLen] != '\0') {
            pwdLen++;
        }
        *enc_pwd = (char*) malloc(sizeof(char) * (37 + pwdLen));
        memcpy(*enc_pwd, "#PWD_INSTAGRAM_BROWSER:0:", 25*sizeof(char));
        memcpy((*enc_pwd)+25, unix_time_s_char, 10*sizeof(char));
        (*enc_pwd)[35] = ':';
        memcpy((*enc_pwd)+36, password, pwdLen*sizeof(char));
        (*enc_pwd)[36+pwdLen] = '\0';

        return 0;
    }

    return 1;
}

int Instagram::getApiToken(char* username, char* enc_pwd, char** csrftoken, char** sessionid) {

    int ua = (rand() / RAND_MAX) % Constants::N_USER_AGENTS;
    *csrftoken = (char*) malloc((32+1) * sizeof(char)); // todo: check more csrf tokens to see if they're always 32 char
    cpr::Response sharedData = cpr::Get(
        cpr::Url{Instagram::SHARED_DATA_URL},
        cpr::Header{{"User-Agent", Constants::USER_AGENTS[ua]}}
    );
    for (const auto &cookie : sharedData.cookies) {
        if (!strcmp(cookie.GetName().c_str(), "csrftoken")) {
            memcpy(*csrftoken, cookie.GetValue().c_str(), 32*sizeof(char));
            (*csrftoken)[32] = '\0';
        }
    }

    cpr::Response loginRequest = cpr::Post(
        cpr::Url{Instagram::LOGIN_URL},
        cpr::Header{
            {"User-Agent", Constants::USER_AGENTS[ua]},
            {"X-CSRFToken", *csrftoken}
        },
        cpr::Payload{
            {"username", username},
            {"enc_password", enc_pwd}
        }
    );

    std::cout << "REQ_COMPLETE" << std::endl;
    std::cout << loginRequest.text << std::endl;
    if (loginRequest.status_code != 200) {
        std::cout << "STATUS_NOT_200" << std::endl;
        std::cout << loginRequest.text << std::endl;
        return 1;
    }

    if (loginRequest.header["authenticated"][0] == 'f') {
        std::cout << "LOGIN INCORRECT" << std::endl;
        return 1;
    }

    for(const auto &cookie : loginRequest.cookies) {
     std::cout << cookie.GetDomain() << ":";
        std::cout << cookie.IsIncludingSubdomains() << ":";
        std::cout << cookie.GetPath() << ":";
        std::cout << cookie.IsHttpsOnly() << ":";
        std::cout << cookie.GetExpiresString() << ":";
        std::cout << cookie.GetName() << ":";
        std::cout << cookie.GetValue() << std::endl;

    }

    //todo: get sessionid cookie
    return 0;
}
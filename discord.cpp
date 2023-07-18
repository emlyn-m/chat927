#include "discord.h"

#include <cpr/cpr.h>

int Discord::sendDM(char* authtoken, char* channelID, char* content) {

    char* send_url = (char*) malloc(sizeof(char) * (
        Discord::SEND_ENDPOINT_FIRST_LENGTH + 
        Discord::CHANNEL_ID_LENGTH + Discord::SEND_ENDPOINT_SECOND_LENGTH));
    for (int i=0; i < Discord::SEND_ENDPOINT_FIRST_LENGTH; i++) { 
        send_url[i] = Discord::SEND_ENDPOINT[i];
    }
    for (int i=0; i <  + Discord::CHANNEL_ID_LENGTH; i++) {
        send_url[i+Discord::SEND_ENDPOINT_FIRST_LENGTH] = channelID[i];
    }
    for (int i = 0; i < Discord::SEND_ENDPOINT_SECOND_LENGTH; i++) {
        send_url[i+Discord::SEND_ENDPOINT_FIRST_LENGTH + Discord::CHANNEL_ID_LENGTH] = "/messages"[i];
    } 
   
    cpr::Response sendRequest = cpr::Post(
        cpr::Url{send_url},
        cpr::Header{{"Authorization", authtoken}},
        cpr::Payload{
            {"content", content},
        }
    );

    if (sendRequest.status_code != 200) {
        return 1;
    }

    return 0;
}
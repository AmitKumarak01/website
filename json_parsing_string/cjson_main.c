#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CJSONParse.h"
#include "CJSONParse.c"

#define CURRENT_CAM_NAME_MAXCHR_LIMIT 256
#define USERNAME_MAXCHR_LIMIT 256              
#define SYSTEMNAME_MAXCHR_LIMIT  256           
//#define DATEFMT_MAXCHR_LIMIT                ((10U) + STR_NULL_CHAR_LN)
#define DATE_MAXCHR_LIMIT 256                  
#define TIME_MAXCHR_LIMIT 256                  
#define TIMEZONE_MAXCHR_LIMIT 256               
#define CURRENT_CAM_NAME_MAXCHR_LIMIT 256      
#define NEXT_CAM_NAME_MAXCHR_LIMIT 256         
#define PREV_CAM_NAME_MAXCHR_LIMIT 256         
#define ROOM_NAME_MAXCHR_LIMIT 256              

typedef enum {
    TYPE_INT,
    TYPE_STR
} KeyType;

typedef struct {
    const char* key;
    KeyType type;
    int maxLength;
    void* value;
} JsonKey;

typedef struct _NotificationParams
{
    int notificationId;

    char userName[USERNAME_MAXCHR_LIMIT];
    char systemName[SYSTEMNAME_MAXCHR_LIMIT];
    char date[DATE_MAXCHR_LIMIT];
    char time[TIME_MAXCHR_LIMIT];
    char timeZone[TIMEZONE_MAXCHR_LIMIT];

    char currentCamName[CURRENT_CAM_NAME_MAXCHR_LIMIT];
    char nextCamName[NEXT_CAM_NAME_MAXCHR_LIMIT];
    char prevCamName[PREV_CAM_NAME_MAXCHR_LIMIT];

    char roomName[ROOM_NAME_MAXCHR_LIMIT];

    int currentMon;
    int currentCam;

    int playbackMon;
    int playbackCam;

    int errorCode;
}NotificationParams;

NotificationParams notifParams = {0};

    
JsonKey jsonKeysList[] = {
    
    {"NCAMN", TYPE_STR, NEXT_CAM_NAME_MAXCHR_LIMIT, notifParams.nextCamName},

    {"ID", TYPE_INT, 0, &notifParams.notificationId},

    //noitifParams.notificationId = Login(ID);
    //{int ID = noitifParams.notificationId}, 

    {"UN", TYPE_STR, USERNAME_MAXCHR_LIMIT, notifParams.userName},
 
    {"DT", TYPE_STR, DATE_MAXCHR_LIMIT, notifParams.date},
 
    {"TM", TYPE_STR, TIME_MAXCHR_LIMIT, notifParams.time},
    //{"LCAMN", TYPE_STR,
    {"CMON", TYPE_INT, 0, &notifParams.currentMon},

    {"CCAM", TYPE_INT, 0, &notifParams.currentCam},

    {"PMON", TYPE_INT, 0, &notifParams.playbackMon},

    {"RM", TYPE_STR, ROOM_NAME_MAXCHR_LIMIT, notifParams.roomName},

    {"ERR", TYPE_INT, 0, &notifParams.errorCode},

    {"PCAM", TYPE_INT, 0, &notifParams.playbackCam},
 
    {"PCAMN", TYPE_STR, PREV_CAM_NAME_MAXCHR_LIMIT, notifParams.prevCamName},

    {"TZ", TYPE_STR, TIMEZONE_MAXCHR_LIMIT, notifParams.timeZone},

    {"SN", TYPE_STR, SYSTEMNAME_MAXCHR_LIMIT, notifParams.systemName},

    {"CCAMN", TYPE_STR, CURRENT_CAM_NAME_MAXCHR_LIMIT, notifParams.currentCamName}

};

void parseNotification(const char*  notificationStrings[], int numNotifications)
{
#if 0
    const char* notificationStrings[] = {
        "{ \"ID\":1,\"UN\":\"John Doe\", \"SN\":\"victor\", \"DT\":\"02/08/2022\", \"TM\":\"12:01:06\" }",
        "{ \"ID\":1,\"UN\":\"Amit\" }",
        "{ \"ID\":2, \"CMON\": 4, \"CCAMN\":\"Training Room\", \"NCAMN\":\"Training Room Corridor\", \"PCAMN\":\"Rear Stairwell\" }",
        "{ \"ID\":2, \"CMON\": 4,\"CCAM\": 1027, \"CCAMN\":null, \"NCAMN\":\"Training Room Corridor\", \"PCAMN\":\"Rear Stairwell\" }",
        "{ \"ID\":3, \"CMON\": 4, \"CCAMN\":\"Training Room\", \"NCAMN\":\"Training Room Corridor\", \"PCAMN\":\"Rear Stairwell\" }",
        "{ \"ID\":4,\"RM\":\"Training Room Rear\",\"PMON\":127,\"PCAM\":1009,\"DT\":\"02/08/2022\",\"TM\":\"12:01:06\",\"TZ\":\"EST\"}",
        "{ \"ID\":5,\"ERR\":1}"

    };
#endif
    for (int i = 0; i < numNotifications; ++i) {
        const char* notifStr = notificationStrings[i];

        cJSON* root = cJSON_Parse(notifStr);
        if (root == NULL) {
            printf("Failed to parse JSON notification string: %s\n", notifStr);
            continue;
        }

        int numKeys = sizeof(jsonKeysList) / sizeof(jsonKeysList[0]);
        printf("=========== sizeof(jsonKeysList): %d \n sizeof(jsonKeysList[0]): %d\n", sizeof(jsonKeysList), sizeof(jsonKeysList[0]));
        for (int j = 0; j < numKeys; ++j) {
            const char* key = jsonKeysList[j].key;
            KeyType keyType = jsonKeysList[j].type;
            void* value = jsonKeysList[j].value;

            cJSON* jsonValue = cJSON_GetObjectItemCaseSensitive(root, key);
            if (jsonValue != NULL) {
                if (keyType == TYPE_INT) {
                    if (jsonValue->type == cJSON_Number) {
                        *(int*)value = jsonValue->valueint;
                    }
                }
                else if (keyType == TYPE_STR) {
                    if (jsonValue->type == cJSON_String) {
                        strncpy((char*)value, jsonValue->valuestring, jsonKeysList[j].maxLength -1);
                        ((char*)value)[jsonKeysList[j].maxLength - 1] = '\0';
                    }
                }
            }
        }

        
        cJSON_Delete(root);

        
        printf("Parsed values for different commands %d:\n", i + 1);
        printf("ID: %d\n", notifParams.notificationId);
        printf("USERNAME: %s\n", notifParams.userName);
        printf("SYSTEMNAME: %s\n", notifParams.systemName);
        printf("DATE: %s\n", notifParams.date);
        printf("TIME: %s\n ",notifParams.time);
        printf("CMON: %d\n", notifParams.currentMon);
        printf("CCAM: %d\n", notifParams.currentCam);
        printf("CCAMN: %s\n", notifParams.currentCamName);
        printf("NCAMN: %s\n", notifParams.nextCamName);
        printf("PCAMN: %s\n", notifParams.prevCamName);
        printf("ROOMNAME: %s\n", notifParams.roomName);
        printf("PMON: %d\n", notifParams.playbackMon);
        printf("PCAM: %d\n", notifParams.playbackCam);
        printf("TIMEZONE: %s\n", notifParams.timeZone);
        printf("ERR: %d\n", notifParams.errorCode);
        printf("Command exit successfully .............\n");
    }
}


int main()
{
    const char *notificationStrings[] = {
        "{ \"ID\":1,\"UN\":\"John Doe\", \"SN\":\"victor\", \"DT\":\"02/08/2022\", \"TM\":\"12:01:06\" }",
        "{ \"ID\":1,\"UN\":\"Amit\" }",
        "{ \"ID\":2, \"CMON\": 4, \"CCAMN\":\"Training Room\", \"NCAMN\":\"Training Room Corridor\", \"PCAMN\":\"Rear Stairwell\" }",
        "{ \"ID\":2, \"CMON\": 4,\"CCAM\": 1027, \"CCAMN\":null, \"NCAMN\":\"Training Room Corridor\", \"PCAMN\":\"Rear Stairwell\" }",
        "{ \"ID\":3, \"CMON\": 4, \"CCAMN\":\"Training Room\", \"NCAMN\":\"Training Room Corridor\", \"PCAMN\":\"Rear Stairwell\" }",
        "{ \"ID\":4,\"RM\":\"Training Room Rear\",\"PMON\":127,\"PCAM\":1009,\"DT\":\"02/08/2022\",\"TM\":\"12:01:06\",\"TZ\":\"EST\"}",
        "{ \"ID\":5,\"ERR\":1}"

    };
    // const char *ptr = "AmitK";
    // printf("size = %lu", strlen(ptr));

    int numNotifications = sizeof(notificationStrings) / sizeof(notificationStrings[0]);
    // printf("==========sizeof(notificationStrings):%d \n sizeof(notificationStrings[0]:%d %d\n", sizeof(notificationStrings), sizeof(notificationStrings[0]));
    // printf("notificationStrings = %p\n", notificationStrings);
    // printf("notificationStrings[0] = %p\n", notificationStrings[0]);
    // printf("notificationStrings[0][0] = %p %c\n", notificationStrings[0][0], notificationStrings[0][0]);
    // printf("notificationStrings[0]/notificationStrings[0][0] = %d\n", sizeof(notificationStrings));
    // parseNotification(notificationStrings, numNotifications);
    printf("size of = %d\n",strlen(notificationStrings));
    printf("size of = %d\n", sizeof(notificationStrings));
    printf("size of = %d\n",sizeof(notificationStrings[0]));
    printf("size of = %d\n",strlen(*notificationStrings));

    return 0;
}

    



// int main()
// {
//     char *json = "{ \"ID\":1,\"UN\":\"John Doe\", \"DT\":\"12/07/2023\", \"TM\":\"12:01:06\" }";
//     //char *json = "{ \"ID\":1 }";
//     //char *j = "{\"ID\":2,\"UN\":\"Amit Kumar\"}";
//     cJSON *row = cJSON_Parse(json);
//     //cJSON *r = cJSON_Parse(j);
//     if(row==NULL)
//     {
//         fprintf(stderr,"Failed to parse the string");
//         return 0;
//     }

//     cJSON *id = cJSON_GetObjectItemCaseSensitive(row, "ID");
//     cJSON *username = cJSON_GetObjectItemCaseSensitive(row, "UN");
//     cJSON *date = cJSON_GetObjectItemCaseSensitive(row,"DT");
//     cJSON *time = cJSON_GetObjectItemCaseSensitive(row, "TM");

//     //if(cJSON_IsNumber(id) && cJSON_IsString(username) && cJSON_IsNumber(date) && cJSON_IsNumber(time))
//     if(json!=NULL)
//     {
//         printf("id: %d\n",id->valueint);
//         printf("username: %s\n",username->valuestring);
//         printf("date: %s\n",date->valuestring);
//         printf("time: %s\n",time->valuestring);       
//     }
        
//     else
//     {
//         printf("JSON in Not Valid \n");
//     }
//     //cJSON *row = cJSON_Parse(json);
//     // if(r==NULL)
//     // {
//     //     fprintf(stderr,"Failed to parse the string");
//     //     return 0;
//     // }

//     // cJSON *id1 = cJSON_GetObjectItemCaseSensitive(r, "ID");
//     // cJSON *username1 = cJSON_GetObjectItemCaseSensitive(r, "UN");

//     // if(j!=NULL)
//     // {
//     //     printf("id: %d\n",id1->valueint);
//     //     printf("username: %s\n",username1->valuestring);
//     // }
     
//     cJSON_Delete(row);

//     //cJSON_Delete(r);
// }

// 
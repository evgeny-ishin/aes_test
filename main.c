#include <stdio.h>
#include "pass_api.h"

#define MAX_AUTH_LENS 60



int main()
{
    size_t key_size = setKeyLength();
    if(!key_size)
    {
        key_size = 16;
    }
    char *key = generateKey(key_size);
    if(key == NULL)
    {
        printf("err key: memory!\n");
        return -1;
    }
    char *solt = generateKey(key_size);
    if(solt == NULL)
    {
        printf("err solt: memory!\n");
        return -1;
    }
    char my_login[MAX_AUTH_LENS];
    memset(my_login, '\0', MAX_AUTH_LENS);
    if(setLogin(my_login,MAX_AUTH_LENS) < 0)
    {
        free(key);
        key = NULL;
        free(solt);
        solt = NULL;
        return -1;
    }
    char my_pass[MAX_AUTH_LENS];
    memset(my_pass, '\0', MAX_AUTH_LENS);
    if(setPassword(my_pass,MAX_AUTH_LENS) < 0)
    {
        free(key);
        key = NULL;
        free(solt);
        solt = NULL;
        return -1;
    }
    char *passw_to_aes = NULL;
    if(convertData(0,key, &passw_to_aes, solt, my_pass, key_size) < 0)
    {
        free(key);
        key = NULL;
        free(solt);
        solt = NULL;
        if(passw_to_aes != NULL)
        {
            free(passw_to_aes);
            passw_to_aes = NULL;
        }
        printf("ERROR: create pass\n");
        return -1;
    }
    char *login_to_aes = NULL;
    if(convertData(0,key, &login_to_aes, solt, my_login, key_size) < 0)
    {
        free(key);
        key = NULL;
        free(solt);
        solt = NULL;
        if(login_to_aes != NULL)
        {
            free(key);
            key = NULL;
            free(solt);
            solt = NULL;
            free(login_to_aes);
            login_to_aes = NULL;
        }
        printf("ERROR: create login\n");
        return -1;
    }
    printf("====================start login AES data=============================\n");
    for(int i = 0; i < strlen(login_to_aes); i++)
    {
        printf("0x%hhu\t",login_to_aes[i]);
        if((i + 1) % 4 == 0) printf("\n");
    }
    printf("======================end login AES data=============================\n");
    printf("\n\n");
    printf("====================start passw AES data=============================\n");
    for(int i = 0; i < strlen(passw_to_aes); i++)
    {
        printf("0x%hhu\t",passw_to_aes[i]);
        if((i + 1) % 4 == 0) printf("\n");
    }
    printf("======================end passw AES data=============================\n");
    printf("\n\n");
    char *passw_from_aes = NULL;
    if(convertData(1,key, &passw_from_aes,solt,passw_to_aes,key_size) < 0)
    {
        free(key);
        key = NULL;
        free(solt);
        solt = NULL;
        if(passw_from_aes != NULL)
        {
           free(passw_from_aes);
           passw_from_aes = NULL;
        }
        return -1;
    }
    char *login_from_aes = NULL;
    if(convertData(1,key, &login_from_aes,solt,login_to_aes,key_size) < 0)
    {
        free(key);
        key = NULL;
        free(solt);
        solt = NULL;
        if(login_from_aes != NULL)
        {
           free(login_from_aes);
           login_from_aes = NULL;
        }
        return -1;
    }
    
    printf("\n\n\n\n");
    printf("login:%s\n", login_from_aes);
    printf("pass:%s\n", passw_from_aes);
    if(passw_to_aes != NULL)
    {
        free(passw_to_aes);
    }
    if(login_to_aes != NULL)
    {
        free(login_to_aes);
    }
    if(passw_from_aes != NULL)
    {
        free(passw_from_aes);
    }
    if(login_from_aes != NULL)
    {
        free(login_from_aes);
    }
    if(solt != NULL)
    {
        free(solt);
    }
    if(key != NULL)
    {
        free(key);
    }
    return 0;
}

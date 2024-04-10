#include "pass_api.h"

int setPassword(char *pass, int size)
{
    if(pass == NULL)
    {
        return -1;
    }
    printf("Set password:");
    if(checkAuthenticationValues(pass, size))
    {
        return -1;
    }
    return 0;
}

int setKeyLength()
{
    printf("You can set key length, available values: 128,192,256\n");
    printf("Please set key length. For default length 128 press 0:");
    int key_length = 0;
    scanf("%d", &key_length);
    getchar();
    printf("key_length = %d\n",key_length);
    if(key_length == 0)
    {
        return 0;
    }
    if((key_length != 128) && (key_length != 192) && (key_length != 256))
    {
        printf("Error: incorrect key length!");
        return 0;
    }
    return key_length / 8;
}

int setLogin(char *login, int size)
{
    if(login == NULL)
    {
        return -1;
    }
    printf("Set login:");
    if(checkAuthenticationValues(login, size))
    {
        return -1;
    }
    return 0;
}

int checkAuthenticationValues(char *value, int size)
{
    if(value == NULL)
    {
        return -1;
    }
    fgets(value,size,stdin);
    for(int i = 0; i < size; i++)
    {
        if((value[i] == '\0') || (value[i] == '\n') || (value[i] == '\t') || (value[i] == '\r') || (value[i] == ' '))
        {
            if(value[i] == 0xA)
            {
                return 0;
            }
            printf("wrong value\n");
            return -1;
        }
    }
    return 0;
}

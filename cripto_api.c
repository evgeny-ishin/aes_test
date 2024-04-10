#include "cripto_api.h"
#include <time.h>

int convertData(unsigned char direction,const char *key, void** out, void* solt,char *input_data, size_t key_length,int *size_of_data)
{
    if(key == NULL)
    {
        return -1;
    }
    enum gcry_cipher_algos algorithm;
    switch(key_length)
    {
    case 24:
        algorithm = GCRY_CIPHER_AES192;
        break;
    case 16:
        algorithm = GCRY_CIPHER_AES128;
        break;
    case 32:
        algorithm = GCRY_CIPHER_AES256;
        break;
    }
    int minimum_block = 16;
    int input_data_len = strlen(input_data);
    char *in_data = NULL;
    int flag_few_input_data = 0;
    if((input_data_len % minimum_block) != 0)
    {
        if(*size_of_data == 0)
        {
            float len =  (float)input_data_len / (float)minimum_block;
            input_data_len = (ceil(len) + 1) * minimum_block;
            *size_of_data = input_data_len;
        }
        else
        {
            if(*size_of_data < 0)
            {
                printf("wrong value for size_of_data\n");
                return -1;
            }
            input_data_len = *size_of_data;
        }
        in_data = (char*)malloc(input_data_len);
        if(in_data == NULL)
        {
            return -1;
        }
        memset(in_data,0x00,input_data_len);
        flag_few_input_data = 1;
        if(*size_of_data > 0)
        {
            memcpy(in_data, input_data, *size_of_data);
        }
        else
        {
            memcpy(in_data, input_data,strlen(input_data));
        }
    }
    else
    {
        in_data = input_data;
    }
    *out = (char*)malloc(input_data_len);
    if(out == NULL)
    {
        return -1;
    }
    size_t solt_len = strlen(solt);
    gcry_error_t err;
    gcry_cipher_hd_t hd;
    size_t key_len = strlen(key);
    err = gcry_cipher_open(&hd,algorithm,GCRY_CIPHER_MODE_CBC,GCRY_CIPHER_CBC_CTS);
    if(err)
    {
        printf("gcry_cipher_open failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
        return -1;
    }
    err = gcry_cipher_setkey(hd,key,key_len);
    if(err)
    {
        printf("gcry_cipher_setkey failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
        return -1;
    }
    err =  gcry_cipher_setiv(hd, solt, solt_len);
    if(err)
    {
        printf("gcry_cipher_setiv failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
        return -1;
    }
    if(!direction)
    {
        err = gcry_cipher_encrypt(hd,*out,input_data_len,in_data,input_data_len);
        if(err)
        {
            printf("gcry_cipher_encrypt failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
            return -1;
        }
    }
    else if(direction == 1)
    {
        err = gcry_cipher_decrypt(hd,*out,input_data_len,in_data,input_data_len);
        if(err)
        {
            printf("gcry_cipher_decrypt failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
            return -1;
        }
    }
    gcry_cipher_close(hd);
    if(flag_few_input_data)
    {
        free(in_data);
    }
    return 0;
}


char* generateKey(size_t key_size)
{
    char *key_out =  (char*)malloc((key_size) + 1);
    if(key_out == NULL)
    {
        return NULL;
    }
    unsigned char byte = 0x00;
    for(int i = 0; i < key_size; i++)
    {
        byte = (unsigned char)(1 + rand() % 254);
        memset(key_out + i, byte, 1);
    }
    key_out[key_size ] = '\0';
    return key_out;
//    char *key_out =  (char*)malloc((key_size) + 1);
//    memset(key_out, byte,key_size);
//    key_out[key_size ] = '\0';
//    return key_out;
}

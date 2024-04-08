#include "cripto_api.h"
#include <time.h>

void convertData(unsigned char direction,const char *key, void** out, void* solt,char *input_data, size_t key_length)
{
    if(key == NULL)
    {
        return;
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
        float len =  (float)input_data_len / (float)minimum_block;
        input_data_len = (ceil(len) + 1) * minimum_block;
        in_data = (char*)malloc(input_data_len);
        if(in_data == NULL)
        {
            return;
        }
        memset(in_data,0x00,input_data_len);
        flag_few_input_data = 1;
        memcpy(in_data, input_data,strlen(input_data));
    }
    else
    {
        in_data = input_data;
    }
    *out = (char*)malloc(input_data_len);
    size_t solt_len = strlen(solt);
    gcry_error_t err;
    gcry_cipher_hd_t hd;
    size_t key_len = strlen(key);
    err = gcry_cipher_open(&hd,algorithm,GCRY_CIPHER_MODE_CBC,GCRY_CIPHER_CBC_CTS);
    if(err)
    {
        printf("gcry_cipher_open failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
    }
    err = gcry_cipher_setkey(hd,key,key_len);
    if(err)
    {
        printf("gcry_cipher_setkey failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
    }
    err =  gcry_cipher_setiv(hd, solt, solt_len);
    if(err)
    {
        printf("gcry_cipher_setiv failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
    }
    if(!direction)
    {
        err = gcry_cipher_encrypt(hd,*out,input_data_len,in_data,input_data_len);
        if(err)
        {
            printf("gcry_cipher_encrypt failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
        }
    }
    else if(direction == 1)
    {
        err = gcry_cipher_decrypt(hd,*out,input_data_len,in_data,input_data_len);
        if(err)
        {
            printf("gcry_cipher_decrypt failed:  %s/%s\n", gcry_strsource(err), gcry_strerror(err));
        }
    }
    gcry_cipher_close(hd);
    if(flag_few_input_data)
    {
        free(in_data);
    }

}


char* generateKey(size_t key_size)
{
    char *key_out =  (char*)malloc((key_size) + 1);
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

#ifndef CRIPTO_API_H
#define CRIPTO_API_H

#include <gcrypt.h>
#include <math.h>

/*!
 * \brief convertData function for convertion data from aes or to aes
 * \param direction 0 - to aes, 1 - from aes
 * \param pass key for encription/decoding
 * \param out - output data
 * \param solt - solt for encription/decoding
 * \param input_data - input data
 * \param key_length - size of key
 */
int convertData(unsigned char direction, const char *pass, void **out, void* solt, char *input_data, size_t key_length);


/*!
 * \brief generateKey function for automatic generate key
 * \param key_size
 * \return
 */
char *generateKey(size_t key_size);

#endif // CRIPTO_API_H

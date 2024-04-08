#ifndef PASS_API_H
#define PASS_API_H

#include "cripto_api.h"

/*!
 * \brief setPassword function for set password
 * \param pass buff for password
 * \param size size of buff
 * \return 0 if successful
 */
int setPassword(char* pass, int size);


/*!
 * \brief setLogin function for set login
 * \param login buff for login
 * \param size size of buff
 * \return 0 if successful
 */
int setLogin(char* login, int size);


/*!
 * \brief setKeyLength function for set key length
 * \return
 */
int setKeyLength();


/*!
 * \brief checkAuthenticationValues
 * \param value for ckecking
 * \param size of value
 * \return
 */
int checkAuthenticationValues(char *value, int size);

#endif // PASS_API_H

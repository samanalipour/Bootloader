/*
 * printf_redirect.h
 *
 *  Created on: Jan 25, 2025
 *      Author: saman
 */

#ifndef APPLICATION_PRINTF_REDIRECT_H_
#define APPLICATION_PRINTF_REDIRECT_H_

#include "main.h"
int _write(int file, char *ptr, int len);
void printArray(const char *arrayName, uint8_t *array, size_t size);

#endif /* APPLICATION_PRINTF_REDIRECT_H_ */
